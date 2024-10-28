/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:26:12 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 17:44:46 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if the argument is a valid number
// Returns 1 if numeric, 0 if not
// Prints error message if not numeric
static int	check_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

// Handles the exit builtin command
// No args: exits with last status
// One numeric arg: exits with that status (modulo 256)
// Non-numeric arg: exits with status 2
// Multiple args: error, status 1, doesn't exit
void	ft_exit(char **command, t_mini *mini)
{
	long	exit_status;

	if (command[1] == NULL)
		ft_close(mini->exit_status, NULL, command, mini);
	if (!check_numeric(command[1]))
		ft_close(2, NULL, command, mini);
	if (command[2] != NULL)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		ft_close(1, NULL, command, mini);
	}
	exit_status = ft_atoi(command[1]);
	while (exit_status < 0)
		exit_status += 256;
	exit_status = exit_status % 256;
	ft_close((int)exit_status, NULL, command, mini);
}
