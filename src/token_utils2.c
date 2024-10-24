/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:15:03 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/24 13:52:33 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//adds t_token variable to the end of the linked list of t_tokens
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

//creates new t_token variable with content set to void * given
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
