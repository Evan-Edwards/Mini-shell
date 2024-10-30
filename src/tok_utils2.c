/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:31:32 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 20:04:00 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*allocate_token(int len)
{
	char	*k;

	k = malloc(len + 1);
	if (!k)
		ft_putstr_fd("malloc error\n", 2);
	return (k);
}

int	handle_token_start(char *s, t_tok *tok, t_mini *mini)
{
	tok->len = len_next(s, tok->i, *mini);
	if (tok->len == 0)
	{
		tok->i++;
		return (1);
	}
	tok->k = allocate_token(tok->len);
	if (!tok->k)
		return (0);
	tok->malloc_flag = 1;
	return (1);
}

int	handle_empty_quotes(char *s, int *i)
{
	if ((s[*i] == '\'' && s[*i + 1] == '\'')
		|| (s[*i] == '\"' && s[*i + 1] == '\"'))
	{
		*i += 2;
		return (1);
	}
	return (0);
}

// Handle special cases for token length calculation
int	handle_special_len(char *str, int i)
{
	if (is_delimiter(str[i]))
	{
		if ((str[i] == '>' || str[i] == '<') && str[i + 1] == str[i])
			return (2);
		return (1);
	}
	if ((str[i] == '\'' && str[i + 1] == '\'')
		|| (str[i] == '\"' && str[i + 1] == '\"'))
		return (0);
	if (str[i] == '$' && (!str[i + 1] || is_delimiter(str[i + 1])
			|| is_quotes(str[i + 1])))
		return (1);
	return (-1);
}

// Calculate length of next token in input string
int	len_next(char *str, int i, t_mini mini)
{
	int	j;
	int	special_len;

	j = 0;
	skip_spaces(str, &i);
	special_len = handle_special_len(str, i);
	if (special_len >= 0)
		return (special_len);
	while (str[i])
	{
		if (!is_quotes(str[i]) || mini.status != DEFAULT)
			j++;
		quotes(str, &i, &mini);
		if (str[i] == '\0')
			break ;
		if (is_delimiter(str[i]) && mini.status == DEFAULT)
			break ;
		i++;
	}
	return (j);
}
