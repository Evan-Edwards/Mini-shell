/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:18 by ttero             #+#    #+#             */
/*   Updated: 2024/10/30 12:30:48 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	handle_delimiter(char *s, int *i, t_mini *mini);
static int	process_delimiter(char *k, int *j, char *s, t_mini *mini);
static int	handle_remaining_token(t_tok *tok, t_mini *mini);

//Initialize token struct
static void	init_token(t_tok *tok)
{
	tok->i = 0;
	tok->j = 0;
	tok->malloc_flag = 0;
	tok->k = NULL;
}

// Calculates length of next token in input string
// Handles quotes and special characters
// Returns 0 for empty quotes
// Returns 1 for lone $ character
static int	len_next(char *str, int i, t_mini mini)
{
	int	j;

	j = 0;
	skip_spaces(str, &i);
	if ((str[i] == '\'' && str[i + 1] == '\'') ||
		(str[i] == '\"' && str[i + 1] == '\"'))
		return (0);
	if (str[i] == '$' && (!str[i + 1] || is_delimiter(str[i + 1]) || is_quotes(str[i + 1])))
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
}

//Allocates memory for new token, returns NULL on error
static char	*allocate_token(int len)
{
	char	*k;

	k = malloc(len + 1);
	if (!k)
		ft_putstr_fd("malloc error\n", 2);
	return (k);
}

//Handle start of new token
static int	handle_token_start(char *s, t_tok *tok, t_mini *mini)
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

//Allocates and initializes a token with one or two characters
static char	*create_token(char c, char *k, int double_char)
{
	if (double_char)
	{
		k = malloc(3);  // For double char + null terminator
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
		k = malloc(2);  // For single char + null terminator
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

//Handles empty quotes, returns 1 if quotes were skipped
static int	handle_empty_quotes(char *s, int *i)
{
	if ((s[*i] == '\'' && s[*i + 1] == '\'') ||
		(s[*i] == '\"' && s[*i + 1] == '\"'))
	{
		*i += 2;
		return (1);
	}
	return (0);
}

//Main tokenization function
int	token(char *s, t_mini *mini)
{
	t_tok	tok;

	init_token(&tok);
	while (s[tok.i])
	{
		if (tok.malloc_flag == 0)
		{
			skip_spaces(s, &tok.i);
			if (handle_empty_quotes(s, &tok.i))
				continue;
			if (!handle_token_start(s, &tok, mini))
				return (0);
		}
		if (!process_char(s, &tok, mini))
			return (0);
	}
	return (handle_remaining_token(&tok, mini));
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
