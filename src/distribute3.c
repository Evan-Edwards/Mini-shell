/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:04:57 by ttero             #+#    #+#             */
/*   Updated: 2024/10/29 15:32:22 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handles individual token processing and updates token types
// Returns 0 for redirection, -1 for error, 1 for success
static int	handle_token(t_token *lst, char **arg_array, int *i)
{
	if (lst->type >= 3)
	{
		lst->next->type = 8;
		return (0);
	}
	arg_array[*i] = ft_strdup(lst->content);
	if (!arg_array[*i])
		return (-1);
	(*i)++;
	return (1);
}

// Processes tokens into argument array until pipe or end
// Returns -1 on error, otherwise returns number of arguments processed
static int	process_token_args(t_token *lst, char **arg_array)
{
	int	i;
	int	result;

	i = 0;
	while (lst->next != NULL && lst->type != PIPE)
	{
		result = handle_token(lst, arg_array, &i);
		if (result == -1)
			return (-1);
		if (result == 0)
			lst = lst->next;
		if (lst->next != NULL)
			lst = lst->next;
	}
	if (lst->type <= 2)
	{
		arg_array[i] = ft_strdup(lst->content);
		if (!arg_array[i])
			return (-1);
		i++;
	}
	arg_array[i] = NULL;
	return (i);
}

// Builds executable argument array from token list
// Returns NULL on error or empty arguments, otherwise returns argument array
char	**build_exe(t_token *lst)
{
	int		arg_num;
	char	**arg_array;
	int		result;

	arg_num = number_of_arguments(lst);
	if (arg_num == 0)
		return (NULL);
	arg_array = malloc(sizeof(char *) * (arg_num + 1));
	if (!arg_array)
		return (NULL);
	result = process_token_args(lst, arg_array);
	if (result == -1)
	{
		free_str_array(arg_array);
		return (NULL);
	}
	return (arg_array);
}

// Resets file descriptors to their original values
// Restores standard input and output
void	reset_dup2(t_mini *mini)
{
	dup2(mini->in, STDIN_FILENO);
	dup2(mini->out, STDOUT_FILENO);
}

// Distributes commands and handles pipe execution
// Returns 1 on success
int	dis_b(t_mini *mini)
{
	t_token	*current;
	int		pipe_num;
	int		i;

	current = mini->lst;
	mini->flag = 0;
	pipe_num = count_pipes(mini->lst);
	i = 0;
	if (pipe_num > 0)
		mini->flag = 1;
	distribute(mini, current);
	while (current != NULL)
	{
		if (current->type == PIPE)
		{
			if (i == pipe_num - 1)
				mini->flag = 0;
			distribute(mini, current->next);
			i++;
		}
		current = current->next;
	}
	reset_dup2(mini);
	return (1);
}
