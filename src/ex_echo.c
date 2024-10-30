/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:43:08 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 18:13:04 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks for -n flag variations in echo command arguments
// Returns 1 if valid -n flags found, 0 otherwise
// Increments index past valid flags
static int	check_n_flag(char **arg, int *i)
{
	int	j;
	int	found_flag;

	found_flag = 0;
	while (arg[*i] && arg[*i][0] == '-' && arg[*i][1] == 'n')
	{
		j = 2;
		while (arg[*i][j] && arg[*i][j] == 'n')
			j++;
		if (arg[*i][j] == '\0')
		{
			found_flag = 1;
			(*i)++;
		}
		else
			break ;
	}
	return (found_flag);
}

// Implements echo builtin command functionality
// Handles -n flag to suppress trailing newline
// Prints arguments with space separation
// Returns 0 on success, -1 on failure
int	ft_echo(char **arg, t_mini *mini)
{
	int		i;
	int		n_flag;
	char	*expanded;

	i = 1;
	n_flag = 0;
	n_flag = check_n_flag(arg, &i);
	while (arg[i])
	{
		expanded = env_var_expansion(arg[i], mini);
		if (!expanded)
			return (-1);
		ft_putstr_fd(arg[i], 1);
		free(expanded);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
