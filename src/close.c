/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 06:29:38 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 15:28:53 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//frees all the memory before exiting
//then exits with the exit status given
void	ft_close(int exit_status, char *input, char **arg, t_mini *mini)
{
	if (input)
		free(input);
	if (arg)
		free_str_array(arg);
	if (mini)
		free_mini(mini);
	exit(exit_status);
}
