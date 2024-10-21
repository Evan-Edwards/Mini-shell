/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:15:03 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/21 11:17:19 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
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
t_token	*ft_lstnew(void *content)
{
	struct s_token	*new;

	new = malloc(sizeof(*new));
	if (!(new))
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	add_to_list(char *k, t_mini *mini)
{
    t_token *new_token;
	char *copy;

	copy = strdup(k);
	new_token = ft_lstnew(copy);
    if (!new_token)
        return (0);
    ft_lstadd_back(&(mini->lst), new_token);
    return (1);
}
//can we use strdup?