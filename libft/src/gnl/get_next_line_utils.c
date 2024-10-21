/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:30:27 by eedwards          #+#    #+#             */
/*   Updated: 2024/07/30 18:26:29 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *stash, char *buf)
{
	char	*s3;
	char	*s3_ptr;

	if (!stash && !buf)
		return (NULL);
	s3 = malloc(ft_strlen(stash) + ft_strlen(buf) + 1);
	if (!s3)
		return (NULL);
	s3_ptr = s3;
	while (*stash)
		*s3++ = *stash++;
	while (*buf)
		*s3++ = *buf++;
	*s3 = '\0';
	return (s3_ptr);
}
