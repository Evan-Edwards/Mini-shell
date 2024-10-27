/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:58:48 by eedwards          #+#    #+#             */
	/*   Updated: 2024/10/27 13:18:11 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free memory before calling
void	ft_perror_close(char *perror_message)
{
	perror(perror_message);
	exit(EXIT_FAILURE);
}

//is it necessary?
//free memory before calling
void		ft_error_close(char **arg, t_mini *mini)
{
	if (arg)
		free_str_array(arg);
	if (mini->envp)
		free_str_array(mini->envp);
	free_mini(mini);
	exit(EXIT_FAILURE);
}

//free memory before calling
//CAN HANDLE MORE ARGS TO FREE?
void		ft_close(char *input, t_mini *mini)
{
	if (input)
		free(input);
	if (mini->envp)
		free_str_array(mini->envp);
	free_mini(mini);
	exit(EXIT_SUCCESS);
}

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

void	free_str_array(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
		free(to_free[i++]);
	free(to_free);
}