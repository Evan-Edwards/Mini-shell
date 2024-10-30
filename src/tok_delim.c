/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_delim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:27:03 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 12:58:23 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirect_out(char *s, int *i, t_mini *mini)
{
	char	*k;
	int		double_char;

	double_char = (s[*i + 1] == '>');
	k = NULL;
	k = create_token(s[*i], k, double_char);
	if (!k)
		return (0);
	add_to_list(k, mini);
	free(k);
	*i += double_char;
	return (1);
}

int	handle_redirect_in(char *s, int *i, t_mini *mini)
{
	char	*k;
	int		double_char;

	k = NULL;
	double_char = (s[*i + 1] == '<');
	k = create_token(s[*i], k, double_char);
	if (!k)
		return (0);
	add_to_list(k, mini);
	free(k);
	*i += double_char;
	return (1);
}

int	handle_pipe(char *s, int *i, t_mini *mini)
{
	char	*k;

	k = NULL;
	k = create_token(s[*i], k, 0);
	if (!k)
		return (0);
	add_to_list(k, mini);
	free(k);
	return (1);
}

int	check_sep(char *s, int *i, t_mini *mini)
{
	if (s[*i] == '>')
		return (handle_redirect_out(s, i, mini));
	else if (s[*i] == '<')
		return (handle_redirect_in(s, i, mini));
	else
		return (handle_pipe(s, i, mini));
}
