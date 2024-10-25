/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:24:59 by ttero             #+#    #+#             */
/*   Updated: 2024/10/25 19:04:31 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
