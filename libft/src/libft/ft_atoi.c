/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:20:50 by eedwards          #+#    #+#             */
/*   Updated: 2024/04/18 15:50:11 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long	result;
	long	check;
	int		sign;

	sign = 1;
	result = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && *str)
	{
		check = result;
		result = result * 10 + *str - '0';
		if (result / 10 != check && sign < 0)
			return (0);
		if (result / 10 != check && sign > 0)
			return (-1);
		str++;
	}
	return ((int)(result * sign));
}

/*The atoi() function converts the initial portion of the string pointed
to by str to int representation. There may be whitespaces before and
one optional + or - sign. The check is to check if it overflows the long
range. If so result will not equal check and it will return 0 for negative
numbers and -1 for positive numbers. */