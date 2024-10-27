/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:04:38 by ttero             #+#    #+#             */
/*   Updated: 2024/06/07 13:04:45 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_error.h"
#include <stdint.h>

int	ft_puthex_error(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len = len + ft_putchar_error(nb + '0');
	else if (nb >= 16 && len >= 0)
	{
		len = len + ft_puthex_error(nb / 16);
		if (len >= 0)
			len = len + ft_puthex_error(nb % 16);
	}
	else if (len >= 0)
	{
		if (nb <= 9)
			len = len + ft_putchar_error(nb + '0');
		else
			len = len + ft_putchar_error(nb - 10 + 'a');
	}
	return (len);
}

int	ft_puthex_error_cap(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len = len + ft_putchar_error(nb + '0');
	else if (nb >= 16 && len >= 0)
	{
		len = len + ft_puthex_error_cap(nb / 16);
		if (len >= 0)
			len = len + ft_puthex_error_cap(nb % 16);
	}
	else if (len >= 0)
	{
		if (nb <= 9)
			len = len + ft_putchar_error(nb + '0');
		else
			len = len + ft_putchar_error(nb - 10 + 'A');
	}
	return (len);
}

int	ft_puthex_error_long(unsigned long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len = len + ft_putchar_error(nb + '0');
	else if (nb >= 16 && len >= 0)
	{
		len = len + ft_puthex_error_long(nb / 16);
		if (len >= 0)
			len = len + ft_puthex_error_long(nb % 16);
	}
	else if (len >= 0)
	{
		if (nb <= 9)
			len = len + ft_putchar_error(nb + '0');
		else
			len = len + ft_putchar_error(nb - 10 + 'a');
	}
	return (len);
}

int	convert_error(void *pointer)
{
	uintptr_t	a;
	int			i;

	if (write(1, "0x", 2) <= 0)
		return (-1);
	i = 2;
	a = (uintptr_t)pointer;
	i = i + ft_puthex_error_long(a);
	return (i);
}
