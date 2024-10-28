/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:03:08 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 13:34:39 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//frees the mini struct
void	free_mini(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->history)
		clear_t_history(mini);
	if (mini->in != -1)
		close(mini->in);
	if (mini->out != -1)
		close(mini->out);
	if (mini->lst)
		free_list(mini->lst);
	if (mini->envp)
		free_str_array(mini->envp);
}

void	free_list(t_token *lst)
{
	t_token	*current;
	t_token	*next;

	current = lst;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
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

//For program exit 
//frees everything in history struct
void	clear_t_history(t_mini *mini)
{
	int	i;

	if (!mini || !mini->history)
		return ;
	rl_clear_history();
	i = 0;
	if (mini->history->commands)
	{
		while (i < mini->history->count && mini->history->commands[i])
		{
			free(mini->history->commands[i]);
			i++;
		}
		free(mini->history->commands);
	}
	free(mini->history);
}

void reset_input(char *input, t_mini *mini)
{
    if (mini->lst)
    {
        free_list(mini->lst);
        mini->lst = NULL;
    }
    if (input)
    {
        free(input);
        input = NULL;
    }
}
