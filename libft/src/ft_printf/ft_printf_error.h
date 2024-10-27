/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:04:26 by ttero             #+#    #+#             */
/*   Updated: 2024/06/07 13:04:33 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_ERROR_H
# define FT_PRINTF_ERROR_H

# include <stdarg.h>
# include <unistd.h>

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
