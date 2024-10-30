/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:31:32 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 19:43:04 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_token(char c, char *k, int double_char)
{
	if (double_char)
	{
		k = malloc(3);
		if (!k)
		{
			ft_putstr_fd("malloc error\n", 2);
			return (NULL);
		}
		k[0] = c;
		k[1] = c;
		k[2] = '\0';
	}
	else
	{
		k = malloc(2);
		if (!k)
		{
			ft_putstr_fd("malloc error\n", 2);
			return (NULL);
		}
		k[0] = c;
		k[1] = '\0';
	}
	return (k);
}

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

/* int	len_next(char *str, int i, t_mini mini)
{
	int	j;

	j = 0;
	skip_spaces(str, &i);
	if (str[i] == '>' || str[i] == '<' || str[i] == '|')
	{
		if ((str[i] == '>' || str[i] == '<') && str[i + 1] == str[i])
			return (2);  // For >> or <<
		return (1);      // For >, <, or |
	}
	if ((str[i] == '\'' && str[i + 1] == '\'')
		|| (str[i] == '\"' && str[i + 1] == '\"'))
		return (0);
	if (str[i] == '$' && (!str[i + 1] || is_delimiter(str[i + 1])
			|| is_quotes(str[i + 1])))
		return (1);
	while (str[i])
	{
		if (is_delimiter(str[i]) && mini.status == DEFAULT)
			break;
		quotes(str, &i, &mini);
		if (str[i] == '\0')
			break;
		i++;
		j++;
	}
	return (j);
} */

int	len_next(char *str, int i, t_mini mini)
{
	int	j;

	j = 0;
	skip_spaces(str, &i);
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
	while (str[i] && !is_delimiter(str[i]) && mini.status == DEFAULT)
	{
		quotes(str, &i, &mini);
		if (str[i] == '\0')
			break ;
		i++;
		j++;
	}
	return (j);
}
