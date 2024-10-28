/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:04:57 by ttero             #+#    #+#             */
/*   Updated: 2024/10/28 06:57:02 by eedwards         ###   ########.fr       */
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

//Processes a token list to build an array of arguments
//Handles redirection tokens (type >= 3) by marking following tokens
//Collects command and argument tokens (type <= 2) into the array
static void	process_token(t_token *lst, char **arg_array, int *i)
{
	while (lst->next != NULL && lst->type != PIPE)
	{
		if (lst->type >= 3)
		{
			lst->next->type = 6;
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
}

//Builds an executable command array from a token list
//Returns NULL if no arguments are found
//Allocates memory for the array and terminates it with NULL
char	**build_exe(t_token *lst)
{
	int		arg_num;
	char	**arg_array;
	int		i;

	i = 0;
	arg_num = number_of_arguments(lst);
	if (arg_num == 0)
		return (NULL);
	arg_array = malloc(sizeof(char *) * (arg_num + 1));
	process_token(lst, arg_array, &i);
	arg_array[i] = 0;
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
			ft_error_close(NULL, arg, mini);
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
	execute_command(arg, mini);
	return (1);
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
	distribute(mini, current);
	while (i < pipe_num)
	{
		if (current->type == PIPE)
		{
			if (i == pipe_num)
				mini->flag = 0;
			distribute(mini, current->next);
			i++;
		}
		current = current->next;
		mini->flag = 0;
	}
	return (1);
}
