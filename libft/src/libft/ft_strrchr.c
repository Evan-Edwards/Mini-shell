/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:34:41 by eedwards          #+#    #+#             */
/*   Updated: 2024/09/04 14:43:29 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = NULL;
	while (*s)
	{
		if (*s == (char)c)
			res = (char *)s;
		s++;
	}
	if (*s == (char)c)
		res = (char *)s;
	return (res);
}

/* scans the string s for the last occurrence of the character c. The scanning 
includes the terminating null character, so the function can also be used to 
locate the end of a string. The pointer res is updated every time the character 
c is found, and finally points to the last occurrence of c or remains NULL if c
is not found. If c is the null character, strrchr locates the terminating \0.*/