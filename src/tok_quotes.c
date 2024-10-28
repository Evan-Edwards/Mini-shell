/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:20:36 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 16:39:30 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	handle_single_quote(int *i, t_mini *mini)
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

static int	handle_double_quote(int *i, t_mini *mini)
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
} */

/*
//checks if the current character is a single or double quote
//uses handle_single_quote and handle_double_quote to
//change mini->status to reflect if next character is in or out of quotes
//if next character is also quote, is_quotes is called again
//returns 0 if not a quote
//returns 1 if successful
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
} */

int quotes(char *s, int *i, t_mini *mini)
{
    char quote_type;

    if (!s || !i || !mini)
        return (1);
    
    quote_type = s[*i];
    if (quote_type == '\'')
    {
        if (mini->status == DEFAULT)
            mini->status = SINGLEQ;
        else if (mini->status == SINGLEQ)
            mini->status = DEFAULT;
    }
    else if (quote_type == '\"')
    {
        if (mini->status == DEFAULT)
            mini->status = DOUBLEQ;
        else if (mini->status == DOUBLEQ)
            mini->status = DEFAULT;
    }
    (*i)++;  // Move past the quote
    return (0);
}
