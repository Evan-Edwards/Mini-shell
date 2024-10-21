/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:42:14 by eedwards          #+#    #+#             */
/*   Updated: 2024/09/04 14:41:50 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		j;
	char	*num;
	long	nbr;

	nbr = (long)n;
	j = num_len(nbr);
	num = malloc(j + 1);
	if (!num)
		return (NULL);
	num[j] = '\0';
	j--;
	if (nbr == 0)
		num[0] = '0';
	if (nbr < 0)
	{
		num[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		num[j] = (nbr % 10) + 48;
		nbr /= 10;
		j--;
	}
	return (num);
}
/*converts int to string. Allocates with malloc for string.
Returns NULL if memory allocation failed*/