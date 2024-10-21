/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:15:29 by eedwards          #+#    #+#             */
/*   Updated: 2024/09/04 14:43:03 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	i;

	if (!s1)
		return (NULL);
	res = (char *) malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
/*The strdup() function allocates sufficient memory for a copy of the string
 s1, does the copy, and returns a pointer to it. The pointer may subsequently
  be used as an argument to the function free(3).
If insufficient memory is available, NULL is returned */