/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:43:08 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 12:26:05 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **arg)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (arg[i] && ft_strcmp(arg[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
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
