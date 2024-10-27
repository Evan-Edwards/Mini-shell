/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:27:15 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 16:13:13 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//prints out next token(s)
void	ft_echo(char **command)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if (command == NULL || command[0] == NULL)
		return ;
	if (command[1] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	if (command[1] == "-n")
	{
		no_newline = 1;
		i++;
	}
	while (command[i])
	{
		ft_printf("%s ", command[i]);
		i++;
	}
	if (no_newline == 0)
		ft_printf("\n");
}
