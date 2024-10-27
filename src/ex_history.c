/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:45:04 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 11:47:43 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ex_history(char **arg, t_history *history)
{
	if (!arg || !history)
	{
		ft_putstr_fd("Error: arg or history is NULL\n", 2);
		return (0);
	}
	if (!arg[1])
		print_history(history);
	else if (arg[1] == "-c")
		clear_t_history(history);
	return (1);
}