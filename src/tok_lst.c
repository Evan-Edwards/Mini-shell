/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:15:03 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 22:24:44 by ttero            ###   ########.fr       */
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
t_token	*ft_t_lstnew(char *content)
{
	struct s_token	*new;
	char			*copy;

	new = malloc(sizeof(*new));
	if (!(new))
		return (NULL);
	copy = ft_strdup(content);
	if (!copy)
	{
		free(new);
		return (NULL);
	}
	new->content = copy;
	new->next = NULL;
	return (new);
}

//prints tokens stored in mini.lst linked list
void	print_list(t_mini *mini)
{
	t_token	*current;

	if (!mini || !mini->lst)
	{
		ft_printf("The list is empty.\n");
		return ;
	}
	current = mini->lst;
	while (current != NULL)
	{
		ft_printf("%s\n", current->content);
		current = current->next;
	}
}

//adds str k to the list stored in mini.lst
//returns 0 if malloc error
//returns 1 if successful
int	add_to_list(char *k, t_mini *mini)
{
	t_token	*new_token;

	if (!k)
		return (0);
	new_token = ft_t_lstnew(k);
	if (!new_token)
		return (0);
	ft_t_lstadd_back(&(mini->lst), new_token);
	return (1);
}
