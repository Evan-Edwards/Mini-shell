/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:04:57 by ttero             #+#    #+#             */
/*   Updated: 2024/10/27 12:52:14 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//This function builds an array of strings (char) from the linked list of tokens
//It allocates memory for the array and copies the content of tokens with type
//ARG, EMPTY, or DASH (2 or lower) into the array.
//???? Is logic correct????
char	**build_exe(t_token *lst)
{
	int		arg_num;
	char	**arg_array;
	int		i;

	arg_num = number_of_arguments(lst);
	arg_array = malloc(sizeof(char *) * (arg_num + 1));
	if (!arg_array)
		return (NULL);
	i = 0;
	while (lst && lst->type != PIPE)
	{
		if (lst->type >= 3)
		{
			lst->next->type = 3;
			lst = lst->next;
		}
		else if (lst->type < 3)
			arg_array[i++] = lst->content;
		if (lst->next != NULL)
			lst = lst->next;
	}
	arg_array[i] = NULL;
	return (arg_array);
}

//checks if function is one of the built in functions
//returns 1 if it is
//0 if not
int	is_builtin(char *arg)
{
	if (ft_strcmp(arg, "echo") == 0)
		return (1);
	if (ft_strcmp(arg, "cd") == 0)
		return (1);
	if (ft_strcmp(arg, "pwd") == 0)
		return (1);
	if (ft_strcmp(arg, "export") == 0)
		return (1);
	if (ft_strcmp(arg, "unset") == 0)
		return (1);
	if (ft_strcmp(arg, "env") == 0)
		return (1);
	if (ft_strcmp(arg, "exit") == 0)
		return (1);
	if (ft_strcmp(arg, "history") == 0)
		return (1);
	return (0);
}

//ERROR HANDLING
int	builtin(char **arg, t_mini *mini, char **envp, t_history *history)
{
	int	status;

	status = 1;
	if (ft_strcmp(arg[0], "cd") == 0)
		status = ft_cd(arg);
	else if (ft_strcmp(arg[0], "echo") == 0)
		ft_echo(arg);
	else if (ft_strcmp(arg[0], "env") == 0)
		status = ft_env(envp);
	else if (ft_strcmp(arg[0], "exit") == 0)
	{
		free_str_array(arg);
		free_str_array(envp);
		ft_close(NULL, history, mini);
	}
	else if (ft_strcmp(arg[0], "export") == 0)
		status = ft_export(arg, envp); // Need to finish
	else if (ft_strcmp(arg[0], "history") == 0)
		status = ex_history(arg, history);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(arg[0], "unset") == 0)
		status = ft_unset(envp, arg);
	return (status);
}

void	execute_command(char **arg, t_mini *mini, char **envp,
	t_history *history)
{
	if (is_builtin(arg[0]) == 1)
	{
		if (builtin(arg, mini, envp, history) == 0)
		{
			ft_putstr_fd("Error: ", 2);
			ft_putstr_fd(arg[0], 2);
			ft_putstr_fd(" command failed\n", 2);
			ft_error_close(arg, mini, envp, history);
		}
	}
	//else
		//exe(arg, mini, envp); //need to finish
}

//handles input and output redirection using file_in and file_out
//builds an argument array using build_exe
//checks if the command is a built-in using is_buildin
//executes the command (either built-in or external)
int distribute(t_mini *mini, char **envp, t_token *lst, t_history history)
{
	int		number_of_commands;
	int		i;
	char	**arg;
	int		file_fd;
	char	*path;

	file_fd = -1;
	if (file_in(mini-) < 0)
	{
		ft_printf("error\n");
		return (0);
	}
	file_fd = file_out(mini);
	if (file_fd < 0)
	{
		ft_printf("error\n");
		return (0);
	}
	number_of_commands = number_of_arguments(mini);
	i = 0;
	arg = build_exe(mini->lst);
	execute_command(arg, mini, envp, history);
	return (1);
}


int	count_pipes (t_token *lst)
{
	int i;

	i = 0;
	if (lst == 0)
		return (0);
	while (lst->next != NULL)
	{
		if (lst ->type == PIPE)
			i++;
		lst = lst->next;
	}
	return (i);
}


int dis_b(t_mini *mini, char **envp, t_history history)
{
	t_token *current;
	int pipe_num;
	int	i;

	current = mini->lst;
	mini->flag = 0;
	pipe_num = count_pipes(mini->lst);
	i = 0;
	if (pipe_num > 0)
		mini->flag = 1;
	distribute(mini, envp, current);
    while (i < pipe_num) 
	{
        if (current->type == PIPE) 
		{
			if (i = pipe_num)
				mini->flag = 0;
			distribute(mini, envp, current->next);
			i++;
        }
        current = current->next;
		mini->flag = 0;
    }
	return (1);
}

