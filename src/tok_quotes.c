/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:20:36 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 18:29:00 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_quote(int *i, t_mini *mini)
{
	if (mini->status == DEFAULT)
	{
		mini->status = SINGLEQ;
		(*i)++;
		return (0);
	}
	else if (mini->status == SINGLEQ)
	{
		mini->status = DEFAULT;
		(*i)++;
		return (0);
	}
	return (1);
}

static int	handle_double_quote(int *i, t_mini *mini)
{
	if (mini->status == DEFAULT)
	{
		mini->status = DOUBLEQ;
		(*i)++;
		return (0);
	}
	else if (mini->status == DOUBLEQ)
	{
		mini->status = DEFAULT;
		(*i)++;
		return (0);
	}
	return (1);
}

int	quotes(char *s, int *i, t_mini *mini)
{
	int	result;

	if (!s || !i || !mini)
		return (1);
	result = 0;
	if (s[*i] == '\'')
		result = handle_single_quote(i, mini);
	else if (s[*i] == '\"')
		result = handle_double_quote(i, mini);
	else
		return (0);
	if (result == 0 && s[*i] && is_quotes(s[*i]))
		return (quotes(s, i, mini));
	return (result);
}
