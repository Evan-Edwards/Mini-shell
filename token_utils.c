/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:12:13 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/21 11:51:31 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isDelimiter(char ch)
{
    if (ch == ' ' || ch == '<' || ch == '>' || ch == '*' )
        return (true);
    return (false);
}
int	is_seperator (char* sep, char c)
{
	int i;

	i = 0;
	//return (0);
	while (i < 1)
	{
		//return (0);
		if (sep[i] == c)
			return 1;
		i++;
		//return (0);
	}
	return 0;
}

int	is_quotes (char *s, int *i)
{
    if (s[*i] == '\'' || (s[*i] == '\"'))
        return (1);
    return (0);
}

void	skip_spaces (char *s, int *i)
{
	if (s[*i] == ' ')
	{
		while (s[*i] == ' ')
		{
			*i++;
		}

	}
}

