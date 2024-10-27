/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:03:11 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 12:36:53 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	print_array(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("%s\n", arg[i]);
		i++;
	}
	printf("%s\n", arg[i]);
}

//counts number of arguments in a linked list of tokens up to end or pipe
//skips tokens of type 3 ?
int	number_of_arguments(t_token *lst)
{
	int	i;

	i = 0;
	while (lst && lst->type != PIPE)
	{
		if (lst->type < 3)
			i++;
		else if (lst->type >= 3 && lst->next)
		{
			lst->next->type = 3;
			lst = lst->next;
		}
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
	return (i);
}
