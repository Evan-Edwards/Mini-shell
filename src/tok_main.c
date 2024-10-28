/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:18 by ttero             #+#    #+#             */
/*   Updated: 2024/10/28 11:37:35 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//makes substr of s from start to end
//adds substr to list with add_to_list
//returns 0 if malloc error, or if add_to_list fails
//returns 1 if successful
static int	add_token(char *s, int start, int end, t_mini *mini)
{
	char	*token;

	if (!s || end < start)
		return (0);
	token = ft_substr(s, start, end - start);
	if (!token)
	{
		ft_putstr_fd("malloc error\n", 2);
		return (0);
	}
	if (!add_to_list(token, mini))
	{
		free(token);
		return (0);
	}
	return (1);
}

//adds delimiters as token to list
//checks if it's a single or double arrow
//returns 0 if malloc error, or if add_to_list fails
//returns 1 if successful
static int	handle_delimiter(char *s, int *i, t_mini *mini)
{
	char	delim[3];

	if (!s || !i || !mini)
		return (0);
	if (s[*i] == '>' || s[*i] == '<' || s[*i] == '|')
	{
		delim[0] = s[*i];
		delim[1] = '\0';
		delim[2] = '\0';
		if ((s[*i] == '>' || s[*i] == '<') && s[*i + 1] == s[*i])
		{
			delim[1] = s[*i];
			(*i)++;
		}
		if (!add_to_list(ft_strdup(delim), mini))
		{
			ft_putstr_fd("malloc error in handle_delimiter\n", 2);
			return (0);
		}
	}
	(*i)++;
	return (1);
}

//sets start of token by skipping spaces
//increments i while s[i] is not a space or delimiter
//uses add_token to make substr given i and start, and add to mini->lst
//uses handle_delimiter to handle delimiters
//returns 0 if malloc error, or if add_token fails
//returns 1 if successful
int	token(char *s, t_mini *mini)
{
	int	i;
	int	start;

	if (!s || !mini)
		return (0);
	i = 0;
	start = 0;
	while (s[i])
	{
		skip_spaces(s, &i);
		start = i;
		while (s[i] && !(is_delimiter(s[i]) && mini->status == DEFAULT))
		{
			if (quotes(s, &i, mini) > 0)
				return (0);
			if (s[i] == '\0')
				break ;
			i++;
		}
		if (i > start && !add_token(s, start, i, mini))
			return (0);
		if (s[i] && is_delimiter(s[i]) && mini->status == DEFAULT)
			if (!handle_delimiter(s, &i, mini))
				return (0);
	}
	return (1);
}

//Takes input string and mini struct
//Expands environmental variables and tokenizes the input
//Returns 0 if malloc error or if expansion/tokenization fails
//Returns 1 if successful
int	input_to_tokens(char *input, t_mini *mini)
{
	char	*expanded_input;

	if (!input || !mini)
		return (0);
	mini->lst = NULL;
	mini->status = DEFAULT;
	expanded_input = env_var_expansion(input, mini);
	if (!expanded_input)
	{
		ft_putstr_fd("error expanding environmental variables\n", 2);
		return (0);
	}
	if (!token(expanded_input, mini))
	{
		free(expanded_input);
		return (0);
	}
	free(expanded_input);
	return (1);
}
