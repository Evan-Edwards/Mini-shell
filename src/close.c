/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 06:29:38 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 10:23:06 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free memory before calling
void	ft_perror_close(char *perror_message)
{
	perror(perror_message);
	exit(EXIT_FAILURE);
}

//free memory before calling
//CAN HANDLE MORE ARGS TO FREE?
void	ft_close(int exit_status, char *input, char **arg, t_mini *mini)
{
	if (input)
		free(input);
	if (arg)
		free_str_array(arg);
	free_mini(mini);
	exit(exit_status);
}
