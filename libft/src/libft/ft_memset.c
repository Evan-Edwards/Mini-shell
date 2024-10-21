/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:52:35 by eedwards          #+#    #+#             */
/*   Updated: 2024/09/04 14:42:34 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)str;
	while (len--)
	{
		*temp = c;
		temp++;
	}
	return (str);
}
/*The memset() function writes len bytes of value c (converted to an unsigned 
char) to the string b.*/