/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:03:08 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 06:32:42 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//frees the mini struct
void	free_mini(t_mini *mini)
{
	t_token	*current;
	t_token	*next;

	if (!mini)
		return ;
	if (mini->history)
		clear_t_history(mini->history);
	current = mini->lst;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	free(mini);
}

//frees array of memory allocated strings
void	free_str_array(char **to_free)
{
	int	i;

	i = 0;
	if (to_free == NULL)
		return ;
	while (to_free[i])
		free(to_free[i++]);
	free(to_free);
}
