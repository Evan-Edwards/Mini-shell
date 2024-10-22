/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:15:03 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/22 10:05:15 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_t_lstadd_back(t_token **lst, t_token *new)
{
	struct s_token	*last;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}
t_token	*ft_t_lstnew(void *content)
{
	struct s_token	*new;

	new = malloc(sizeof(*new));
	if (!(new))
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

//can we use strdup?