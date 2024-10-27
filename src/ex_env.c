/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:47:50 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 10:23:29 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//prints environmental variables
//success: returns 1
//failure: Prints error message and returns 0
int	ft_env(char **envp)
{
	while (*envp)
	{
		if (ft_putstr(*envp) == -1 || ft_putchar('\n') == -1)
		{
			ft_putstr_fd("Printing error", 2);
			return (0);
		}
		envp++;
	}
	return (1);
}
