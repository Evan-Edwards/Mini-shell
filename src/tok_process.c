/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:25:14 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 19:37:10 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Process a single character from the input string
int	process_char(char *s, t_tok *tok, t_mini *mini)
{
	quotes(s, &tok->i, mini);
	if (s[tok->i] == '\0')
		return (1);
	if (is_delimiter(s[tok->i]) && mini->status == DEFAULT)
	{
		if (!handle_token2(tok, mini))
			return (0);
		if (!check_sep(s, &tok->i, mini))
			return (0);
		return (1);
	}
	if (ft_isspace(s[tok->i]) && mini->status == DEFAULT)
		handle_token2(tok, mini);
	else if (tok->k)
		tok->k[tok->j++] = s[tok->i];
	tok->i++;
	return (1);
}

// Handle token by adding it to the list if not empty
int	handle_token2(t_tok *tok, t_mini *mini)
{
	if (!tok->k || tok->j == 0)
		return (1);
	tok->k[tok->j] = '\0';
	if (ft_strlen(tok->k) > 0)
		add_to_list(tok->k, mini);
	free(tok->k);
	tok->k = NULL;
	tok->malloc_flag = 0;
	tok->j = 0;
	return (1);
}

int	process_delimiter(char *k, int *j, char *s, t_mini *mini)
{
	int	i;

	i = *j;
	k[i] = '\0';
	if (ft_strlen(k) > 0)
		add_to_list(k, mini);
	free(k);
	if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		check_sep(s, j, mini);
	return (1);
}

int	handle_remaining_token(t_tok *tok, t_mini *mini)
{
	if (tok->k)
	{
		tok->k[tok->j] = '\0';
		if (ft_strlen(tok->k) > 0)
			add_to_list(tok->k, mini);
		free(tok->k);
		tok->k = NULL;
	}
	return (1);
}
