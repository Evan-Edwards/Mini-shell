/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:44:26 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 10:20:31 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//joins together the cwd and path to make new dest str
//adds first / to the end of cwd
//returns NULL if ft_strjoin fails
static char	*cat_cwd_path(char *cwd, char *path)
{
	char	*temp;
	char	*dest;

	temp = ft_strjoin(cwd, "/");
	if (temp == NULL)
		return (NULL);
	dest = ft_strjoin(temp, path);
	free(temp);
	return (dest);
}

//handles '.' and '..' in the path
//removes last directory for '..' and skips '.'
//updates index i to skip processed characters
//returns NULL if rm_last_dir fails, updated cwd otherwise
static char	*handle_dot_paths(char *cwd, char *path, int *i)
{
	char	*new_cwd;

	if (path[*i] == '.' && path[*i + 1] == '.')
	{
		new_cwd = rm_last_dir(cwd);
		free(cwd);
		if (new_cwd == NULL)
			return (NULL);
		cwd = new_cwd;
		*i += 2;
		if (path[*i] == '/')
			(*i)++;
	}
	else if (path[*i] == '.')
	{
		(*i)++;
		while (path[*i] == '/')
			(*i)++;
	}
	return (cwd);
}

//creates a new path by joining cwd with the remaining part of path
//extracts substring of path from index i to end
//joins extracted path with cwd using cat_cwd_path
//frees temporary allocations and returns new combined path
//returns NULL if memory allocation fails
static char	*handle_alpha_path(char *cwd, char *path, int i)
{
	char	*temp_path;
	char	*new_cwd;

	temp_path = ft_substr(path, i, ft_strlen(path) - i);
	if (temp_path == NULL)
	{
		free(cwd);
		return (NULL);
	}
	new_cwd = cat_cwd_path(cwd, temp_path);
	free(cwd);
	free(temp_path);
	return (new_cwd);
}

//uses cwd and path to create new dest str
//if there's "..": removes last directory
//otherwise adds path to cwd to create dest
char	*mod_cwd(char *cwd, char *path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '.')
		{
			cwd = handle_dot_paths(cwd, path, &i);
			if (cwd == NULL)
				return (NULL);
		}
		else if (ft_isalpha(path[i]) == 1)
			return (handle_alpha_path(cwd, path, i));
		else
			i++;
	}
	return (cwd);
}
