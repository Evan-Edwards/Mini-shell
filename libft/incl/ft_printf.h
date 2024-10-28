/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:28:45 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 06:37:52 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

# define DEC "0123456789"
# define HEX "0123456789ABCDEF"
# define HEX_LOW "0123456789abcdef"

int	ft_printf(const char *str, ...);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(long nb, int len, char *base, int *count);
int	ft_putnbr_p(unsigned long nb, unsigned long len, char *base);
int	ft_printf_error(const char *s, ...);
int	ft_putchar_error(int c);
int	ft_putnbr_mod_error(int nb);
int	ft_put_unsig_error(unsigned int nb);
int	ft_putstr_error(char *str);
int	ft_puthex_error(unsigned int nb);
int	ft_puthex_error_cap(unsigned int nb);
int	ft_puthex_error_long(unsigned long nb);
int	convert_error(void *pointer);

#endif
