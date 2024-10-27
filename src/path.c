/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:24:59 by ttero             #+#    #+#             */
/*   Updated: 2024/10/27 18:23:12 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Checks if the last character of argv is a slash and handles directory error
//Returns NULL after printing error message and exiting if it's a directory
char	*handle_dir_slash(char *argv)
{
	int	i;

	i = ft_strlen(argv) - 1;
	if (argv[i] == '/')
	{
		ft_printf_error("%s: Is a directory\n", argv);
		exit(126);
	}
	return (NULL);
}

//Handles absolute path for the given argv
//Returns a duplicate of argv if accessible, exits with appropriate error
//otherwise
char	*handle_absolute_path(char *argv)
{
	if (access(argv, F_OK) == 0)
	{
		if (access(argv, X_OK) == 0)
			return (ft_strdup(argv));
		ft_printf_error("%s: Permission denied\n", argv);
		exit(126);
	}
	else
	{
		ft_printf_error("%s: No such file or directory\n", argv);
		exit(127);
	}
}

//Handles relative path for the given argv
//Returns the result of find_path function or exits with error if PATH is
//not set
char	*handle_relative_path(char *argv, char **envp)
{
	int	i;

	i = is_env(envp);
	if (i == -1)
	{
		ft_printf_error("%s: No such file or directory\n", argv);
		exit(127);
	}
	return (find_path(argv, envp));
}

//Gets the path for the given argv
//Returns the appropriate path based on whether it's absolute or relative
char	*get_path(char *argv, char **envp)
{
	char	*result;

	result = handle_dir_slash(argv);
	if (result)
		return (result);
	if (argv[0] == '/' || (argv[0] == '.' && argv[1] == '/'))
		return (handle_absolute_path(argv));
	return (handle_relative_path(argv, envp));
}
