/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:27:15 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 10:27:46 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//prints out next token(s)
void	ft_echo(char **command)
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
