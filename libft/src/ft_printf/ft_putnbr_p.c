/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:37:59 by eedwards          #+#    #+#             */
/*   Updated: 2024/05/27 10:45:38 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	ft_h(unsigned long nb, unsigned long len, char *base, int *count)
{
	if (*count == -1)
		return ;
	if (nb >= len)
		ft_h(nb / len, len, base, count);
	if (ft_putchar(base[nb % len]) == -1)
		*count = -1;
	else
		(*count)++;
}

int	ft_putnbr_p(unsigned long nb, unsigned long len, char *base)
{
	int	count;

	count = 0;
	if (ft_putstr("0x") == -1)
		return (-1);
	count = 2;
	ft_h(nb, len, base, &count);
	return (count);
}
