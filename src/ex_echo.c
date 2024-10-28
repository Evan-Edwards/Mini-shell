/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:27:15 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 16:00:30 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Prints command tokens starting from given index, adding spaces between words
static void	print_echo_content(char **command, int start)
{
	while (command[start])
	{
		ft_printf("%s", command[start]);
		if (command[start + 1])
			ft_printf(" ");
		start++;
	}
}

//prints out next token(s)
int	ft_echo(char **command)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if (command == NULL || command[0] == NULL)
		return (EXIT_FAILURE);
	if (command[1] == NULL)
	{
		ft_printf("\n");
		return (EXIT_SUCCESS);
	}
	if (ft_strcmp(command[1], "-n") == 0)
	{
		no_newline = 1;
		i++;
	}
	print_echo_content(command, i);
	if (no_newline == 0)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
