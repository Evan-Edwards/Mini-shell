/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:53:35 by ttero             #+#    #+#             */
/*   Updated: 2024/10/29 18:05:14 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Checks for syntax errors in the token list
//Returns 1 if no errors, 0 if errors are found
int	check_errors(t_token *lst)
{
	t_token	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp)
	{
		if (temp->type >= 3)
		{
			if (temp->next == NULL || temp->next->type >= 3)
			{
				ft_putstr_fd("syntax error near unexpected token, ", 2);
				ft_putstr_fd(temp->content, 2);
				ft_putstr_fd("\n", 2);
				return (0);
			}
		}
		temp = temp->next;
	}
	return (1);
}

static void	expand_exit_status(t_token *token, t_mini *mini)
{
	char	*exit_status_str;

	if (strcmp(token->content, "$?") == 0)
	{
		exit_status_str = ft_itoa(mini->exit_status);
		if (!exit_status_str)
			return ;
		free(token->content);
		token->content = exit_status_str;
	}
}

//Determines the type of a token based on its content
//Returns the corresponding token type
int	reg(char *str)
{
	if (str[0] == '\0')
		return (EMPTY);
	else if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APPEND);
		return (OUTPUT);
	}
	else if (str[0] == '<')
	{
		if (str[1] == '<')
			return (HEREDOC);
		return (INPUT);
	}
	else if (str[0] == '-')
		return (DASH);
	else if (str[0] == '|')
		return (PIPE);
	else
		return (ARG);
}

//Sets the type for each token in the linked list
//Returns 1 on success, 0 if the list is empty
int	set_types(t_token *lst, t_mini *mini)
{
	if (!lst)
		return (0);
	while (lst)
	{
		expand_exit_status(lst, mini);
		lst->type = reg(lst->content);
		lst = lst->next;
	}
	return (1);
}

//Counts the number of pipe tokens in the linked list
//Returns the count of pipes
int	count_pipes(t_token *lst)
{
	int	i;

	i = 0;
	if (lst == 0)
		return (0);
	while (lst->next != NULL)
	{
		if (lst ->type == PIPE)
			i++;
		lst = lst->next;
	}
	return (i);
}
