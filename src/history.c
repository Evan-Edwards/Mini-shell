/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:52:22 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 07:23:37 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Initializes history struct
//Returns 1 on success, 0 on failure
int	init_history(t_history **history)
{
	*history = (t_history *)malloc(sizeof(t_history));
	if (!(*history))
		return (0);
	(*history)->capacity = 100;
	(*history)->count = 0;
	(*history)->commands = malloc((*history)->capacity * sizeof(char *));
	if (!(*history)->commands)
	{
		free(*history);
		*history = NULL;
		return (0);
	}
	return (1);
}

//Adds command to history struct
//Returns 1 on success, 0 on failure
int	add_to_history(t_history *history, char *command)
{
	char	*new_command;

	if (!history || !command || history->count >= history->capacity)
		return (0);
	new_command = ft_strdup(command);
	if (!new_command)
	{
		ft_putstr_fd("Error: memory allocation failed\n", 2);
		return (0);
	}
	history->commands[history->count] = new_command;
	history->count++;
	return (1);
}

//Prints history struct
//Returns 1 on success, 0 if history is NULL
int	print_history(t_history *history)
{
	int	i;

	if (!history)
		return (0);
	i = 0;
	while (i < history->count)
	{
		ft_printf("%d: %s\n", i + 1, history->commands[i]);
		i++;
	}
	return (1);
}

//For history -c command: clear contents but keep structure
int	clear_history_contents(t_history *history)
{
	int	i;

	if (!history)
		return (0);
	rl_clear_history();
	i = 0;
	while (i < history->count)
	{
		free(history->commands[i]);
		i++;
	}
	history->count = 0;  // Just reset the count, keep the allocated array
	return (1);
}

//Adds command to readline history and history struct
//Returns 1 on success, 0 on failure
int	ft_history(char *command, t_mini *mini)
{
	if (!command || !mini)
	{
		ft_putstr_fd("Error: invalid arguments\n", 2);
		return (0);
	}
	add_history(command);
	if (!mini->history)
	{
		if (!init_history(&mini->history))
		{
			ft_putstr_fd("Error: failed to initialize history\n", 2);
			return (0);
		}
	}
	return (add_to_history(mini->history, command));
}
