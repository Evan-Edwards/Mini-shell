/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:05:03 by eedwards          #+#    #+#             */
/*   Updated: 2024/09/04 14:42:23 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	cc;
	unsigned char	*str;

	cc = (unsigned char)c;
	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == cc)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
/* the memchr() function locates the first occurence of c (converted to an
unsigned char) in string s. The n parameter tells how many bytes we want to
search in (necessary because there's no terminating character)*/
