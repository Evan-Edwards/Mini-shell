/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:43:08 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 19:45:22 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:43:08 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 12:30:00 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks for -n flag variations in echo command arguments.
 * Returns 1 if valid -n flags are found, 0 otherwise.
 * Increments index i past any valid flags.
 *
 * @param arg The argument list.
 * @param i Pointer to the current index in the argument list.
 * @return 1 if -n flags are found, 0 otherwise.
 */
static int	check_n_flag(char **arg, int *i)
{
	int	j;
	int	found_flag = 0;

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
			break; // Stop if the flag is not a valid -n variation
	}
	return (found_flag);
}

/**
 * Implements the echo builtin command functionality.
 * Handles -n flag to suppress trailing newline.
 * Prints arguments with space separation.
 * Returns 0 on successful execution.
 *
 * @param arg The argument list.
 * @param mini The shell's state containing environment variables.
 * @return 0 on success, -1 on failure.
 */
int	ft_echo(char **arg, t_mini *mini)
{
	int	i;
	int	n_flag;
	char	*expanded;

	i = 1;
	n_flag = 0;
	n_flag = check_n_flag(arg, &i);
	while (arg[i])
	{
		expanded = env_var_expansion(arg[i], mini);
		if (!expanded)
			return (-1); // Handle memory allocation failure appropriately
		ft_putstr_fd(expanded, 1);
		free(expanded);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
