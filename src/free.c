/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:03:08 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 07:27:54 by eedwards         ###   ########.fr       */
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
		clear_t_history(mini);
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

//For program exit: free everything
void	clear_t_history(t_mini *mini)
{
	int	i;

	if (!mini->history)
		return ;
	rl_clear_history();
	i = 0;
	while (i < mini->history->count)
	{
		free(mini->history->commands[i]);
		i++;
	}
	free(mini->history->commands);
	free(mini->history);
}
