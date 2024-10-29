/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:43:08 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 15:37:56 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks for -n flag variations in echo command arguments
// Returns 1 if valid -n flags found, 0 otherwise
// Increments index i past any valid flags
static int	check_n_flag(char **arg, int *i)
{
	int	j;

	while (arg[*i] && arg[*i][0] == '-' && arg[*i][1] == 'n')
	{
		j = 2;
		while (arg[*i][j] == 'n')
			j++;
		if (arg[*i][j] == '\0')
			(*i)++;
		else
			return (0);
	}
	return (1);
}

// Implements echo builtin command functionality
// Handles -n flag to suppress trailing newline
// Prints arguments with space separation
// Returns 0 on successful execution
int	ft_echo(char **arg)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (check_n_flag(arg, &i))
		n_flag = 1;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
