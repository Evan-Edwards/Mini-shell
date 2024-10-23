/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:24:59 by ttero             #+#    #+#             */
/*   Updated: 2024/10/23 20:28:37 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_dir_slash(char *argv, t_data data)
{
	int	i;

	i = ft_strlen(argv) - 1;
	if (argv[i] == '/')
	{
		ft_printf_error("%s: Is a directory\n", argv);
		free_struct(data);
		exit(126);
	}
	return (NULL);
}

char	*handle_absolute_path(char *argv, t_data data)
{
	if (access(argv, F_OK) == 0)
	{
		if (access(argv, X_OK) == 0)
			return (ft_strdup(argv));
		ft_printf_error("%s: Permission denied\n", argv);
		free_struct(data);
		exit(126);
	}
	else
	{
		ft_printf_error("%s: No such file or directory\n", argv);
		free_struct(data);
		exit(127);
	}
}

char	*handle_relative_path(char *argv, char **envp, t_data data)
{
	int	i;

	i = is_env(envp);
	if (i == -1)
	{
		ft_printf_error("%s: No such file or directory\n", argv);
		free_struct(data);
		exit(127);
	}
	return (find_path(argv, envp));
}

char	*get_path(char *argv, char **envp, t_data data)
{
	char	*result;

	result = handle_dir_slash(argv, data);
	if (result)
		return (result);
	if (argv[0] == '/' || (argv[0] == '.' && argv[1] == '/'))
		return (handle_absolute_path(argv, data));
	return (handle_relative_path(argv, envp, data));
}
