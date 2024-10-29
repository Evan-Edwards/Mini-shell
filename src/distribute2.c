/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:03:11 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 10:46:35 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_array(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("%s\n", arg[i]);
		i++;
	}
	printf("%s\n", arg[i]);
}

//counts number of arguments in a linked list of tokens up to end or pipe
//skips tokens of type 3 ?
int	number_of_arguments(t_token *lst)
{
	int	i;

	i = 0;
	while (lst && lst->type != PIPE)
	{
		if (lst->type < 3)
			i++;
		else if (lst->type >= 3 && lst->next)
		{
			lst->next->type = 8;
			lst = lst->next;
		}
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
	return (i);
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

//Executes built-in shell commands (cd, echo, env, exit, history, pwd, unset)
//Returns 1 on success, 0 on failure
//Handles command-specific logic and error reporting
int	builtin(char **arg, t_mini *mini)
{
	if (ft_strcmp(arg[0], "cd") == 0)
		mini->exit_status = ft_cd(arg);
	else if (ft_strcmp(arg[0], "echo") == 0)
		mini->exit_status = ft_echo(arg);
	else if (ft_strcmp(arg[0], "env") == 0)
		mini->exit_status = ft_env(mini->envp);
	else if (ft_strcmp(arg[0], "exit") == 0)
		ft_exit(arg, mini);
	else if (ft_strcmp(arg[0], "export") == 0)
		mini->exit_status = ft_export(arg, mini);
	else if (ft_strcmp(arg[0], "history") == 0)
		mini->exit_status = ex_history(arg, mini->history);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		mini->exit_status = ft_pwd();
	else if (ft_strcmp(arg[0], "unset") == 0)
		mini->exit_status = ft_unset(arg, mini);
	return (mini->exit_status);
}
