/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:04:17 by ttero             #+#    #+#             */
/*   Updated: 2024/06/07 13:04:21 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_error.h"

int	dis(va_list *va, char c)
{
	if (c == 'd' || c == 'i')
		return (ft_putnbr_mod_error(va_arg(*va, int)));
	if (c == 'c')
		return (ft_putchar_error(va_arg(*va, int)));
	if (c == 's')
		return (ft_putstr_error(va_arg(*va, char *)));
	if (c == '%')
		return (ft_putchar_error(c));
	if (c == 'x')
		return (ft_puthex_error(va_arg(*va, unsigned long)));
	if (c == 'X')
		return (ft_puthex_error_cap(va_arg(*va, unsigned long)));
	if (c == 'u')
		return (ft_put_unsig_error(va_arg(*va, unsigned int)));
	if (c == 'p')
		return (convert_error(va_arg(*va, void *)));
	else
		return (-1);
}

int	ft_printf_error_loop(va_list *va, const char *s, int i, int j)
{
	int	k;

	while (s[i])
	{
		if (s[i] == '%')
		{
			k = dis(va, s[i + 1]);
			i++;
		}
		else
			k = ft_putchar_error(s[i]);
		if (k < 0)
			return (-1);
		j = j + k;
		i++;
	}
	return (j);
}

int	ft_printf_error(const char *s, ...)
{
	int		i;
	va_list	va;
	int		j;

	i = 0;
	j = 0;
	va_start(va, s);
	j = ft_printf_error_loop(&va, s, i, j);
	va_end(va);
	return (j);
}
