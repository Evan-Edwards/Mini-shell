/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:20:36 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/25 13:28:55 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_quote(char *s, int *i, t_mini *mini)
{
	if (mini->status == DEFAULT)
	{
		mini->status = SINGLEQ;
		(*i)++;
	}
	else if (mini->status == SINGLEQ)
	{
		mini->status = DEFAULT;
		(*i)++;
	}
	else
		return (1);
	return (0);
}

static int	handle_double_quote(char *s, int *i, t_mini *mini)
{
	if (mini->status == DEFAULT)
	{
		mini->status = DOUBLEQ;
		(*i)++;
	}
	else if (mini->status == DOUBLEQ)
	{
		mini->status = DEFAULT;
		(*i)++;
	}
	else
		return (1);
	return (0);
}

//checks if the current character is a single or double quote
//uses handle_single_quote and handle_double_quote to
//change mini->status to reflect if next character is in or out of quotes
//if next character is also quote, is_quotes is called again
int	quotes(char *s, int *i, t_mini *mini)
{
	int	result;

	result = 0;
	if (s[*i] == '\'')
		result = handle_single_quote(s, i, mini);
	else if (s[*i] == '\"')
		result = handle_double_quote(s, i, mini);
	else
		return (0);
	if (result == 0 && is_quotes(s[*i]))
		quotes(s, i, mini);
	return (0);
}
