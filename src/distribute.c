/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:04:57 by ttero             #+#    #+#             */
/*   Updated: 2024/10/28 13:56:44 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	**build_exe(t_token *lst)
{
	int		arg_num;
	char	**arg_array;
	int		i;

	i = 0;
	arg_num = number_of_arguments(lst);
	if (arg_num == 0)
	{
		return (NULL);
	}
	arg_array = malloc(sizeof(char*) * (arg_num +1));
	while (lst->next != NULL && lst->type != PIPE)
	{
		if (lst->type >= 3)
		{
			lst->next->type = 6;
			lst = lst->next;
		}
		else
		{
			arg_array[i] = lst->content;
			i++;
		}
		if (lst->next != NULL)
			lst = lst->next;
	}
	if (lst->type <= 2)
	{
		arg_array[i] = lst->content;
		i++;
	}
	//arg_array[i] = malloc(1);
	arg_array[i] = 0;
	return (arg_array);
}*/

/* //Processes a token list to build an array of arguments
//Handles redirection tokens (type >= 3) by marking following tokens
//Collects command and argument tokens (type <= 2) into the array
static void	process_token(t_token *lst, char **arg_array, int *i)
{
	while (lst->next != NULL && lst->type != PIPE)
	{
		if (lst->type >= 3)
		{
			lst->next->type = 8;
			lst = lst->next;
		}
		else
		{
			arg_array[*i] = lst->content;
			(*i)++;
		}
		if (lst->next != NULL)
			lst = lst->next;
	}
	if (lst->type <= 2)
	{
		arg_array[*i] = lst->content;
		(*i)++;
	}
} */


//Processes a single token and updates the argument array
//Returns: -1 on allocation error, 0 for redirection tokens, 1 for normal tokens
//Updates: arg_array with new argument, i with new array position
static int handle_token(t_token *lst, char **arg_array, int *i)
{
    if (lst->type >= 3)
    {
        lst->next->type = 8;
        return (0);
    }
    arg_array[*i] = ft_strdup(lst->content);
    if (!arg_array[*i])
        return (-1);
    (*i)++;
    return (1);
}

//Processes tokens to build array of command arguments
//Returns: -1 on allocation error, otherwise number of arguments processed
//Handles: Command tokens, arguments, and marks redirection targets
//Updates: arg_array with arguments, NULL terminated
static int process_token_args(t_token *lst, char **arg_array)
{
	int i;
	int result;

	i = 0;
	while (lst->next != NULL && lst->type != PIPE)
	{
		result = handle_token(lst, arg_array, &i);
		if (result == -1)
			return (-1);
		if (result == 0)
			lst = lst->next;
		if (lst->next != NULL)
			lst = lst->next;
	}
	if (lst->type <= 2)
	{
		arg_array[i] = ft_strdup(lst->content);
		if (!arg_array[i])
			return (-1);
		i++;
	}
	arg_array[i] = NULL;
	return (i);
}

//Builds an executable command array from a token list
//Returns NULL if no arguments are found or on allocation failure
//Allocates memory for the array and terminates it with NULL
//Caller must free the returned array using free_str_array
char **build_exe(t_token *lst)
{
    int     arg_num;
    char    **arg_array;
    int     result;

    arg_num = number_of_arguments(lst);
    if (arg_num == 0)
        return (NULL);
    arg_array = malloc(sizeof(char *) * (arg_num + 1));
    if (!arg_array)
        return (NULL);
    result = process_token_args(lst, arg_array);
    if (result == -1)
    {
        free_str_array(arg_array);
        return (NULL);
    }
    return (arg_array);
}

//Executes a command, either built-in or external
//Checks command type and routes to appropriate handler
//Reports errors for failed built-in commands
void	execute_command(char **arg, t_mini *mini)
{
	if (is_builtin(arg[0]) == 1)
	{
		if (builtin(arg, mini) == 0)
		{
			ft_putstr_fd("Error: ", 2);
			ft_putstr_fd(arg[0], 2);
			ft_putstr_fd(" command failed\n", 2);
			ft_close(1, NULL, arg, mini);
		}
	}
	else
		exe(arg, mini); //need to finish
}

//Handles input and output redirection using file_in and file_out
//Builds an argument array using build_exe
//Checks if the command is a built-in using is_builtin
//Executes the command (either built-in or external)
//Returns 0 on error, 1 on success
int	distribute(t_mini *mini, t_token *current)
{
	char	**arg;
	int		file_fd;

	file_fd = -1;
	if (file_in(current) < 0)
	{
		ft_printf("error\n");
		return (0);
	}
	file_fd = file_out(current);
	if (file_fd < 0)
	{
		ft_printf("error\n");
		return (0);
	}
	arg = build_exe(current);
	if (arg == NULL)
		return (0);
	execute_command(arg, mini);
	free_str_array(arg);
	return (1);
}

void	reset_dup2(t_mini *mini)
{
	dup2(mini->in, STDIN_FILENO);
	dup2(mini->out, STDOUT_FILENO);
}


//Distributes commands across pipes
//Processes multiple commands separated by pipes
//Sets flags for pipe handling and manages command flow
int	dis_b(t_mini *mini)
{
	t_token	*current;
	int		pipe_num;
	int		i;

	current = mini->lst;
	mini->flag = 0;
	pipe_num = count_pipes(mini->lst);
	i = 0;
	if (pipe_num > 0)
		mini->flag = 1;
	// Execute first command
	distribute(mini, current);
	
	// Move to next commands after pipes
	while (current != NULL)
	{
		if (current->type == PIPE)
		{
			if (i == pipe_num - 1)  // Last pipe
				mini->flag = 0;
			distribute(mini, current->next);
			i++;
		}
		current = current->next;
	}
	reset_dup2(mini);
	return (1);
}
