/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:20:00 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 16:55:29 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//allocates memory for path string
//calls get_cwd to get path string + handles errors
//returns cwd or NULL + prints error message if fails
char	*get_current_directory(void)
{
	char	*cwd;
	size_t	size;

	size = 4096;
	cwd = malloc(size);
	if (cwd == NULL)
	{
		ft_putstr_fd("Malloc Error\n", 2);
		return (NULL);
	}
	if (getcwd(cwd, size) == NULL)
	{
		free (cwd);
		ft_putstr_fd("Get cwd failed\n", 2);
		return (NULL);
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
	{
		if (cwd)
			free(cwd);
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
