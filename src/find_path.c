/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:25:25 by ttero             #+#    #+#             */
/*   Updated: 2024/10/28 06:29:13 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Copies characters from src to dest starting at the given index
//Updates index to point to the next available position in dest
void	copy_string(char *dest, const char *src, int *index)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[*index] = src[i];
		(*index)++;
		i++;
	}
}

//Joins two strings and frees the first string (s1)
//Returns newly allocated string containing s1+s2, or NULL if allocation fails
char	*ft_strjoin_mod(char *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*arr;
	int		i;

	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	arr = (char *)malloc(len1 + len2 + 1);
	if (!arr)
		return (NULL);
	i = 0;
	copy_string(arr, s1, &i);
	copy_string(arr, s2, &i);
	arr[i] = '\0';
	free(s1);
	return (arr);
}

//Searches environment variables for PATH
//Returns index of PATH variable or -1 if not found
//Handles NULL environment and empty environment cases
int	is_env(char *env[])
{
	int	i;

	i = 0;
	if (env == NULL || env[0] == NULL)
		return (-1);
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (env[i] == NULL)
		return (-1);
	if (ft_strnstr(env[i], "PATH", 4) != 0)
		return (i);
	return (-1);
}

//Searches PATH environment for executable file
//Returns full path to executable if found, NULL otherwise
//Handles path construction and validation
char	*find_path(char *argv, char *env[])
{
	int		i;
	char	**token;
	char	*path;

	i = 0;
	i = is_env(env);
	if (i == -1)
		return (NULL);
	token = ft_split(env[i] + 5, ':');
	i = 0;
	while (token[i] != NULL)
	{
		path = ft_strjoin(token[i], "/");
		path = ft_strjoin_mod(path, argv);
		if (access(path, F_OK) == 0)
		{
			free_str_array(token);
			return (path);
		}
		free(path);
		i++;
	}
	free_str_array(token);
	return (NULL);
}
