/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:18 by ttero             #+#    #+#             */
/*   Updated: 2024/10/30 19:43:35 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Initialize token struct
static void	init_token(t_tok *tok)
{
	tok->i = 0;
	tok->j = 0;
	tok->malloc_flag = 0;
	tok->k = NULL;
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
				continue ;
			if (is_delimiter(s[tok.i]) && mini->status == DEFAULT)
			{
				if (!check_sep(s, &tok.i, mini))
					return (0);
				continue ;
			}
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
