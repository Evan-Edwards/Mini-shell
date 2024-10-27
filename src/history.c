/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:52:22 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 12:06:45 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//initialises history struct
t_history	*init_history(void)
{
	t_history	*history;

	history = (t_history *)malloc(sizeof(t_history));
	if (!history)
		return (NULL);
	history->capacity = 100;
	history->count = 0;
	history->commands = (char **)malloc(history->capacity * sizeof(char *));
	if (!history->commands)
	{
		free(history);
		return (NULL);
	}
	return (history);
}

//adds command to history struct
void	add_to_history(t_history *history, char *command)
{
	if (history->count < history->capacity)
	{
		history->commands[history->count] = ft_strdup(command);
		history->count++;
	}
	else
	{
		ft_printf("History capacity reached\n");
	}
}

//prints history struct
void	print_history(t_history *history)
{
	int	i;

	if (!history)
		return ;
	i = 0;
	while (i < history->count)
	{
		ft_printf("%d: %s\n", i + 1, history->commands[i]);
		i++;
	}
}

void	clear_t_history(t_history *history)
{
	if (!history)
		return ;
	rl_clear_history();
	free(history->commands);
	free(history);
}

//adds history to readline history
//initiates history struct if not already done
//then adds input to history struct
//returns history struct
void	ft_history(char *command, t_history *history)
{
	if (!command)
	{
		ft_putstr_fd("Error: command is NULL\n", 2);
		return ;
	}
	add_history(command);
	if (!history)
	{
		history = init_history();
		if (!history)
		{
			ft_putstr_fd("Error: failed to initialize history\n", 2);
			return ;
		}
	}
	add_to_history(history, command);
}
