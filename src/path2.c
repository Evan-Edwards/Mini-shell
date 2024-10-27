/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:24:54 by ttero             #+#    #+#             */
/*   Updated: 2024/10/27 18:23:47 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Checks if the last character of the argv is a slash
//Returns 0 if it's a directory, 1 otherwise
int	handle_dir_slash2(char *argv)
{
	int	i;

	i = ft_strlen(argv) - 1;
	if (argv[i] == '/')
	{
		ft_printf_error("%s: Is a directory\n", argv);
		return (0);
	}
	return (1);
}

//Handles absolute path for the given argv
//Returns a duplicate of argv if accessible, NULL otherwise
char	*handle_absolute_path2(char *argv)
{
	if (access(argv, F_OK) == 0)
	{
		if (access(argv, X_OK) == 0)
			return (ft_strdup(argv));
		ft_printf_error("%s: Permission denied\n", argv);
		return (NULL);
	}
	else
	{
		ft_printf_error("%s: No such file or directory\n", argv);
		return (NULL);
	}
	return (NULL);
}

//Handles relative path for the given argv
//Returns the result of find_path function
char	*handle_relative_path2(char *argv, char **envp)
{
	return (find_path(argv, envp));
}

//Gets the path for the given argv
//Returns the appropriate path or NULL if not found
char	*get_path2(char *argv, char **envp)
{
	char	*result;
	int		check;
	int		i;

	check = handle_dir_slash2(argv);
	if (check == 0)
		return (NULL);
	if (argv[0] == '/' || (argv[0] == '.' && argv[1] == '/'))
	{
		return (handle_absolute_path2(argv));
	}
	i = is_env(envp);
	if (i == -1)
	{
		ft_printf_error("%s: No such file or directory\n", argv);
		return (NULL);
	}
	result = handle_relative_path2(argv, envp);
	if (result == NULL)
		ft_printf_error("%s: command not found:\n", argv);
	return (result);
}
