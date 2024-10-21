/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:55:16 by eedwards          #+#    #+#             */
/*   Updated: 2024/09/04 13:20:33 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_stash(char **stash)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
}

static char	*set_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (stash[i] == '\0')
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	if (!line)
		return (NULL);
	return (line);
}
/*If there is a new line and characters afterwards sets stash to the remaining
characters after new line, otherwise frees and nulls stash.*/

static char	*next_stash(char *stash)
{
	int		i;
	char	*temp;

	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i++;
	if ((stash)[i] == '\0')
	{
		free_stash(&stash);
		return (NULL);
	}
	temp = ft_substr(stash, i, ft_strlen(stash) - i);
	if (!temp)
	{
		free_stash(&stash);
		return (NULL);
	}
	free_stash(&stash);
	return (temp);
}

/*If there is a new line and characters afterwards sets stash to the remaining
characters after new line*/

static char	*fill_stash(int fd, char **stash, char *buf)
{
	ssize_t	b_read;
	char	*temp;

	b_read = 1;
	if (!*stash)
		*stash = ft_strdup("");
	if (!*stash)
		return (NULL);
	while (b_read != 0 && !ft_strchr(*stash, '\n') && *stash)
	{
		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read == -1)
		{
			free_stash(stash);
			return (NULL);
		}
		buf[b_read] = '\0';
		if (b_read == 0)
			break ;
		temp = *stash;
		*stash = ft_strjoin_gnl(*stash, buf);
		free(temp);
	}
	return (*stash);
}
/*reads through fd while buf does not contain a new line or NULL. It joins stash
and buf together and continues until buf does contain a new line or NULL*/

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[MAX_FD];
	char		*buf;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || !buf)
	{
		free_stash(&stash[fd]);
		free_stash(&buf);
		return (NULL);
	}
	stash[fd] = fill_stash(fd, &stash[fd], buf);
	free (buf);
	if (!stash[fd])
		return (NULL);
	line = set_line(stash[fd]);
	if (!line)
	{
		free_stash(&stash[fd]);
		return (NULL);
	}
	stash[fd] = next_stash(stash[fd]);
	return (line);
}
/*Checks first that fd and BUFFER_SIZE are valid. It then fills the stash with 
fill_stash, gets the line to be output will set_line, and then set's the stash 
to be used the next time with next_stash.*/
