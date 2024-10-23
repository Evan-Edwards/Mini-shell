/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:58:48 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/23 16:42:15 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror_close(char *perror_message)
{
	perror(perror_message);
	exit(EXIT_FAILURE);
}

//is it necessary?
void	ft_error_close(char *error_message)
{
	ft_printf("Error: %s\n", error_message);
	//free memory
	exit(EXIT_FAILURE);
}

void	ft_close(void)
{
	//free all allocated memory
	exit(EXIT_SUCCESS);
}
