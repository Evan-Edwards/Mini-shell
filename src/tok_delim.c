/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_delim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:27:03 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 19:32:31 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirect_out(char *s, int *i, t_mini *mini)
{
	char	*k;
	int		double_char;

	double_char = (s[*i + 1] == '>');
	k = create_token(s[*i], NULL, double_char);
	if (!k)
		return (0);
	add_to_list(k, mini);
	free(k);
	*i += 1 + double_char;
	return (1);
}

int	handle_redirect_in(char *s, int *i, t_mini *mini)
{
	char	*k;
	int		double_char;

	double_char = (s[*i + 1] == '<');
	k = create_token(s[*i], NULL, double_char);
	if (!k)
		return (0);
	add_to_list(k, mini);
	free(k);
	*i += 1 + double_char;
	return (1);
}

int	handle_pipe(char *s, int *i, t_mini *mini)
{
	char	*k;

	k = create_token(s[*i], NULL, 0);
	if (!k)
		return (0);
	add_to_list(k, mini);
	free(k);
	*i += 1;
	return (1);
}

int	check_sep(char *s, int *i, t_mini *mini)
{
	if (s[*i] == '>')
		return (handle_redirect_out(s, i, mini));
	else if (s[*i] == '<')
		return (handle_redirect_in(s, i, mini));
	else if (s[*i] == '|')
		return (handle_pipe(s, i, mini));
	return (1);
}

int	handle_delimiter(char *s, int *i, t_mini *mini)
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
		if (!add_to_list(delim, mini))
		{
			ft_putstr_fd("malloc error in handle_delimiter\n", 2);
			return (0);
		}
		(*i)++;
	}
	return (1);
}
