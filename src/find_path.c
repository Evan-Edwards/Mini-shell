/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:25:25 by ttero             #+#    #+#             */
/*   Updated: 2024/10/23 20:33:10 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_token(char **cmd1)
{
	int	i;

	i = -1;
	while (cmd1[++i])
		free(cmd1[i]);
	free(cmd1);
}

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
			free_token(token);
			return (path);
		}
		free(path);
		i++;
	}
	free_token(token);
	return (NULL);
}
