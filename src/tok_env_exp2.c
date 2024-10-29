/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_exp2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:11:40 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 18:23:28 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handles special cases for environment variable expansion
static char	*handle_special_env(char *str, int *i, t_mini *mini)
{
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(mini->exit_status));
	}
	if (!str[*i] || is_delimiter(str[*i]))
	{
		(*i)--;
		return (ft_strdup("$"));
	}
	return (NULL);
}

// Gets environment variable value or returns empty string
static char	*get_env_value(char *str, int *i, t_mini *mini)
{
	int		start;
	char	*var_name;
	char	*env_val;
	char	*result;

	start = ++(*i);
	result = handle_special_env(str + start, i, mini);
	if (result)
		return (result);
	while (str[*i] && !is_delimiter(str[*i]))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (NULL);
	env_val = getenv(var_name);
	free(var_name);
	if (env_val)
		result = ft_strdup(env_val);
	else
		result = ft_strdup("");
	return (result);
}

char	*process_env_vars(char *str, char *copy, t_mini *mini)
{
	int	i;
	int	j;
	int	in_quotes;

	i = 0;
	j = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' && mini->status == DEFAULT)
			in_quotes = !in_quotes;
		if (str[i] == '$' && (in_quotes || mini->status == DEFAULT))
		{
			if (!handle_dollar(str, &i, copy, &j, mini))
				return (NULL);
		}
		else if ((str[i] == '\'' || str[i] == '\"')
			&& mini->status == DEFAULT)
			copy_quoted(str, &i, copy, &j);
		else
			copy[j++] = str[i++];
	}
	copy[j] = '\0';
	return (copy);
}

static void	copy_quoted(char *str, int *i, char *copy, int *j)
{
	if (str[*i] == '"')
		copy_double_quoted(str, i, copy, j);
	else
		copy_single_quoted(str, i, copy, j);
}

char	*process_env_vars(char *str, char *copy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!handle_dollar(str, &i, copy, &j))
				return (NULL);
		}
		else if (str[i] == '\'' || str[i] == '\"')
			copy_quoted(str, &i, copy, &j);
		else
			copy[j++] = str[i++];
	}
	copy[j] = '\0';
	return (copy);
}
