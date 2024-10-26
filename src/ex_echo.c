/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:27:15 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/26 17:23:42 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//prints out next token
void	ex_echo(char **command)
{
	int	i;

	i = 1;
	while (command[i])
	{
		ft_printf("%s ", command[i]);
		i++;
	}
	ft_printf("\n");
}
