/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:58:48 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/26 17:15:51 by eedwards         ###   ########.fr       */
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
void	ft_error_close(char *error_message)
{
	ft_printf("Error: %s\n", error_message);
	exit(EXIT_FAILURE);
}

//free memory before calling
void	ft_close(char *input, t_history *history)
{
	if (input)
		free(input);
	if (history)
		clear_t_history(history);
	free_mini(mini);
	exit(EXIT_SUCCESS);
}

void	free_mini(t_mini *mini)
{
	t_token	*current;
	t_token	*next;

	if (!mini)
		return ;
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
