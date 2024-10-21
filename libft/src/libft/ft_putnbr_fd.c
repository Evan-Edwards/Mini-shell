/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:33:09 by eedwards          #+#    #+#             */
/*   Updated: 2024/09/04 14:42:44 by eedwards         ###   ########.fr       */
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

static void	itoa(long nbr, char *num, int len)
{
	num[len] = '\0';
	len--;
	if (nbr == 0)
		num[0] = '0';
	if (nbr < 0)
	{
		num[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		num[len] = (nbr % 10) + 48;
		nbr /= 10;
		len--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	int		len;
	char	nbr_str[12];

	nbr = (long)n;
	len = num_len(nbr);
	itoa(nbr, nbr_str, len);
	ft_putstr_fd(nbr_str, fd);
}
