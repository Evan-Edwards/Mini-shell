/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:18 by ttero             #+#    #+#             */
/*   Updated: 2024/10/27 11:37:58 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//makes substr of s from start to end
//adds substr to list with add_to_list
//FIX ERROR HANDLING
static void	add_token(char *s, int start, int end, t_mini *mini)
{
	char	*token;

	token = ft_substr(s, start, end - start);
	if (!token)
		ft_putstr_fd("malloc error\n", 2); //FIX
	add_to_list(token, mini);
	free(token);
}

//adds delimiters as token to list
//checks if it's a single or double arrow
static void	handle_delimiter(char *s, int *i, t_mini *mini)
{
	char	delim[3];

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
		add_to_list(delim, mini);
	}
	(*i)++;
}

//sets start of token by skipping spaces
//increments i while s[i] is not a space or delimiter
//uses add_token to make substr given i and start, and add to mini->lst
//uses handle_delimiter to handle delimiters
void	token(char *s, t_mini *mini)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (s[i])
	{
		skip_spaces(s, &i);
		start = i;
		while (s[i] && !(is_delimiter(s[i]) && mini->status == DEFAULT))
		{
			quotes(s, &i, mini);
			if (s[i] == '\0')
				break ;
			i++;
		}
		if (i > start)
			add_token(s, start, i, mini);
		if (is_delimiter(s[i]) && mini->status == DEFAULT)
			handle_delimiter(s, &i, mini);
	}
}

//ERROR HANDLING FOR TOKEN?
void	input_to_tokens(char *input, char **envp, t_mini *mini)
{
	mini->lst = NULL;
	mini->status = DEFAULT;
	input = env_var_expansion(input, envp, mini);
	if (input == NULL)
	{
		free_mini(mini);
		ft_putstr_fd("Error expanding environmental variables\n", 2);
		ft_error_close(NULL, mini, envp, NULL); //FIX
	}
	token(input, mini);
}
