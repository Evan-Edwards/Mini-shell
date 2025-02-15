/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:50:25 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 11:13:34 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//If successful, calloc() returns a pointer to allocated memory. The allocated
//memory is filled with bytes of value zero. If there is an error, they return
//a NULL pointer and set errno to ENOMEM.
void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	if (count > 0 && size > 0 && count > SIZE_MAX / size)
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, size * count);
	return (tmp);
}
