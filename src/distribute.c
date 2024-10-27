/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:04:57 by ttero             #+#    #+#             */
/*   Updated: 2024/10/27 18:08:30 by eedwards         ###   ########.fr       */
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
int	builtin(char **arg, t_mini *mini)
{
	int	status;

	status = 1;
	if (ft_strcmp(arg[0], "cd") == 0)
		status = ft_cd(arg);
	else if (ft_strcmp(arg[0], "echo") == 0)
		ft_echo(arg);
	else if (ft_strcmp(arg[0], "env") == 0)
		status = ft_env(mini->envp);
	else if (ft_strcmp(arg[0], "exit") == 0)
	{
		free_str_array(arg);
		ft_close(NULL, mini);
	}
	//else if (ft_strcmp(arg[0], "export") == 0)
	//	status = ft_export(arg, mini); // Need to finish
	else if (ft_strcmp(arg[0], "history") == 0)
		status = ex_history(arg, mini->history);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(arg[0], "unset") == 0)
		status = ft_unset(mini->envp, arg);
	return (status);
}

void	execute_command(char **arg, t_mini *mini)
{
	if (is_builtin(arg[0]) == 1)
	{
		if (builtin(arg, mini) == 0)
		{
			ft_putstr_fd("Error: ", 2);
			ft_putstr_fd(arg[0], 2);
			ft_putstr_fd(" command failed\n", 2);
			ft_error_close(arg, mini);
		}
	}
	//else
		//exe(arg, mini, envp); //need to finish
}

//handles input and output redirection using file_in and file_out
//builds an argument array using build_exe
//checks if the command is a built-in using is_buildin
//executes the command (either built-in or external)
int distribute(t_mini *mini, t_token *current)
{
	char	**arg;
	int		file_fd;

	file_fd = -1;
	if (file_in(current) < 0) //does it need to be current?
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

int dis_b(t_mini *mini)
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
