/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:12:13 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/21 20:27:18 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isDelimiter(char ch)
{
    if (ch == ' ' || ch == '<' || ch == '>' || ch == '*' )
        return (true);
    return (false);
}

bool is_quotes (char ch)
{
    if (ch == '\''|| ch == '\"')
        return (true);
    return (false);
}

void	skip_spaces (char *s, int *i)
{
	if (s[*i] == ' ')
	{
		while (s[*i] == ' ')
		{
			*i = *i + 1;
		}

	}
}

