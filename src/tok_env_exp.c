/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/29 18:16:03 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_dollar(char *copy, int *i, int *j)
{
	copy[*j] = '$';
	(*i)++;
	(*j)++;
	return (1);
}

static int	handle_dollar_str(char *str, int *i)
{
	return (!str[*i + 1] || str[*i + 1] == '"'
		|| str[*i + 1] == '\'' || is_delimiter(str[*i + 1]));
}

static int	handle_dollar(char *str, int *i, char *copy, int *j)
{
	char	*env_val;
	size_t	val_len;

	if (handle_dollar_str(str, i))
		return (handle_single_dollar(copy, i, j));
	env_val = get_env_value(str, i);
	if (!env_val)
		return (0);
	val_len = ft_strlen(env_val);
	ft_strlcpy(copy + *j, env_val, val_len + 1);
	*j += val_len;
	free(env_val);
	return (1);
}

static void	copy_double_quoted(char *str, int *i, char *copy, int *j)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			if (!handle_dollar(str, i, copy, j))
				return ;
		}
		else
		{
			copy[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
	}
	if (str[*i])
		(*i)++;
}

static void	copy_single_quoted(char *str, int *i, char *copy, int *j)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		copy[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	if (str[*i])
		(*i)++;
}
