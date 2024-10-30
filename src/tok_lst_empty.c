/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_lst_empty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:24:26 by ttero             #+#    #+#             */
/*   Updated: 2024/10/30 22:32:51 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_t_lstsize(t_token *lst)
{
	int		nodes;
	t_token	*current;

	current = lst;
	nodes = 0;
	while (current)
	{
		current = current->next;
		nodes++;
	}
	return (nodes);
}

void	add_empty(t_mini *mini)
{
	t_token	*empty_token;

	if (ft_t_lstsize(mini->lst) == 0)
		return ;
	empty_token = ft_t_lstnew("");
	if (!empty_token)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return ;
	}
	ft_t_lstadd_back(&(mini->lst), empty_token);
}
