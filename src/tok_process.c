/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:25:14 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 14:58:48 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

int	process_char(char *s, t_tok *tok, t_mini *mini)
{
	quotes(s, &tok->i, mini);
	if (s[tok->i] == '\0')
		return (1);
	if (is_delimiter(s[tok->i]) && mini->status == DEFAULT)
	{
		if (tok->k == NULL)
			return (1);
		process_delimiter(tok->k, &tok->j, s, mini);
		tok->k = NULL;
		tok->malloc_flag = 0;
		tok->j = 0;
	}
	else
		tok->k[tok->j++] = s[tok->i];
	tok->i++;
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
