/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:24:59 by ttero             #+#    #+#             */
/*   Updated: 2024/10/30 12:07:36 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if the last character of argv[0] is a slash and handles directory error
// Returns NULL after printing error message and calling ft_close if it's a directory
char	*handle_dir_slash(char *argv, char **arg, t_mini *mini)
{
	int	i;

	i = ft_strlen(argv) - 1;
	if (argv[i] == '/')
	{
		ft_printf_error("%s: Is a directory\n", argv);
		ft_close(126, NULL, arg, mini);
	}
	return (NULL);
}

// Handles absolute path for the given argv[0]
// Returns a duplicate of argv if accessible, calls ft_close otherwise
char	*handle_absolute_path(char *argv, char **arg, t_mini *mini)
{
	if (access(argv, F_OK) == 0)
	{
		if (access(argv, X_OK) == 0)
			return (ft_strdup(argv));
		ft_printf_error("%s: Permission denied\n", argv);
		ft_close(126, NULL, arg, mini);
	}
	else
	{
		ft_printf_error("%s: No such file or directory\n", argv);
		ft_close(127, NULL, arg, mini);
	}
	return (NULL);
}

// Handles relative path for the given argv[0]
// Returns the result of find_path function or calls ft_close if PATH is not set
char	*handle_relative_path(char *argv, char **envp, char **arg, t_mini *mini)
{
	int	i;

	i = is_env(envp);
	if (i == -1)
	{
		ft_printf_error("%s: No such file or directory\n", argv);
		ft_close(127, NULL, arg, mini);  
	}
	return (find_path(argv, envp));
}

// Gets the path for the given argv[0]
// Returns the appropriate path based on whether it's absolute or relative
char	*get_path(char **argv, char **envp, t_mini *mini)
{
	char	*result;

	result = handle_dir_slash(argv[0], argv, mini);
	if (result)
		return (result);
	if (argv[0][0] == '/' || (argv[0][0] == '.' && argv[0][1] == '/'))
		return (handle_absolute_path(argv[0], argv, mini));
	return (handle_relative_path(argv[0], envp, argv, mini));
}
