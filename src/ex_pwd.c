/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:20:00 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/25 13:37:36 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//allocates memory for path string
//calls get_cwd to get path string + handles errors
//returns cwd
char	*get_current_directory(void)
{
	char	*cwd;
	size_t	size;

	size = 4096;
	cwd = malloc(size);
	if (cwd == NULL)
		ft_error_close("Malloc Error"); //will it work like this? Need to free stuff?
	if (getcwd(cwd, size) == NULL)
	{
		free (cwd);
		ft_perror_close("getcwd failed");
	}
	return (cwd);
}

//gets path string from get_current directory
//prints path string
//frees cwd
//returns 0 if fails, 1 if succeeds
int	ft_pwd(void)
{
	char	*cwd;

	cwd = get_current_directory();
	if (cwd == NULL)
		return (0);
	ft_printf("Current working directory: %s\n", cwd);
	free(cwd);
	return (1);
}