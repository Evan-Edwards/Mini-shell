/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:04:04 by ttero             #+#    #+#             */
/*   Updated: 2024/06/07 13:04:12 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_error.h"

int	ft_putchar_error(int c)
{
	return (write(2, &c, 1));
}

int	ft_putnbr_mod_error(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
		return (write(2, "-2147483648", 11));
	if (nb < 0)
	{
		len = len + ft_putchar_error('-');
		nb *= -1;
	}
	if (nb >= 10 && len >= 0)
	{
		len = len + ft_putnbr_mod_error(nb / 10);
		if (len >= 0)
			len = len + ft_putnbr_mod_error(nb % 10);
	}
	else if (len >= 0)
	{
		len = len + ft_putchar_error(nb + '0');
	}
	return (len);
}

int	ft_put_unsig_error(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb >= 10)
	{
		len = len + ft_put_unsig_error(nb / 10);
		if (len >= 0)
			len = len + ft_put_unsig_error(nb % 10);
	}
	else if (len >= 0)
	{
		len = len + ft_putchar_error(nb + '0');
	}
	return (len);
}

int	ft_putstr_error(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (write(2, "(null)", 6));
	while (str[i] != '\0')
	{
		if (write(2, &str[i], 1) < 0)
			return (-1);
		i++;
		j++;
	}
	return (j);
}
