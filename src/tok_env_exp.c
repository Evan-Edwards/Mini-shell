/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/29 20:23:27 by eedwards         ###   ########.fr       */
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

int	handle_dollar(char *str, int *i, char *copy, int *j, t_mini *mini)
{
	char	*env_val;
	size_t	val_len;

	if (handle_dollar_str(str, i))
		return (handle_single_dollar(copy, i, j));
	env_val = get_env_value(str, i, mini);
	if (!env_val)
		return (0);
	val_len = ft_strlen(env_val);
	ft_strlcpy(copy + *j, env_val, val_len + 1);
	*j += val_len;
	free(env_val);
	return (1);
}

int	handle_env_var(char *str, int *i, char *copy, int *j, t_mini *mini)
{
	char	*env_val;
	size_t	val_len;

	env_val = get_env_value(str, i, mini);
	if (!env_val)
		return (0);
	val_len = ft_strlen(env_val);
	ft_strlcpy(copy + *j, env_val, val_len + 1);
	*j += val_len;
	free(env_val);
	return (1);
}

void	copy_double_quoted(char *str, int *i, char *copy, int *j, t_mini *mini)
{
	int	ret;

	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			ret = handle_dollar(str, i, copy, j, mini);
			if (ret == 0)
				return ;
			if (ret == 2 && !handle_env_var(str, i, copy, j, mini))
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

void	copy_single_quoted(char *str, int *i, char *copy, int *j)
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
