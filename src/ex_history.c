/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:45:04 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 16:06:06 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ex_history(char **arg, t_history *history)
{
	if (!arg || !history)
	{
		ft_putstr_fd("Error: arg or history is NULL\n", 2);
		return (EXIT_FAILURE);
	}
	if (!arg[1])
		print_history(history);
	else if (ft_strcmp(arg[1], "-c") == 0)
		clear_history_contents(history);
	return (EXIT_SUCCESS);
}
