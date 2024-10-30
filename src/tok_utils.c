/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:12:13 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 19:19:47 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_delimiter(char ch)
{
	if (ch == '<' || ch == '>' || ch == '*' || ch == '|')
		return (true);
	return (false);
}

bool	is_quotes(char ch)
{
	if (ch == '\'' || ch == '\"')
		return (true);
	return (false);
}

void	skip_spaces(char *s, int *i)
{
	while (ft_isspace(s[*i]))
		(*i)++;
}

// Reallocates memory for the copy string if needed
// Returns the new (or unchanged) copy string
char	*add_copy_size(char *copy, size_t new_total_size)
{
	char	*new_copy;

	if (!copy)
		return (NULL);
	new_copy = malloc(new_total_size);
	if (!new_copy)
	{
		free(copy);
		return (NULL);
	}
	ft_strlcpy(new_copy, copy, new_total_size);
	free(copy);
	return (new_copy);
}
