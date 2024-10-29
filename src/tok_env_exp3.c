/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_exp3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/29 20:23:20 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Gets length of environment variable value
//Returns length or 0 on error
static size_t	get_env_len(char *str, int *i)
{
	int		start;
	char	*var_name;
	char	*env_val;
	size_t	len;

	start = ++(*i);
	while (str[*i] && !is_delimiter(str[*i]))
		(*i)++;
	if (*i == start)
		return (1);
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (1);
	env_val = getenv(var_name);
	free(var_name);
	if (!env_val)
		return (0);
	len = ft_strlen(env_val);
	if (len)
		return (len);
	return (1);
}

//Handles size calculation for quoted content
//Returns size of content within quotes
static size_t	handle_quotes(char *str, int *i, char quote_type)
{
	size_t	size;

	size = 2;
	(*i)++;
	while (str[*i] && str[*i] != quote_type)
	{
		size++;
		(*i)++;
	}
	if (str[*i])
		(*i)++;
	return (size);
}

//Calculates size needed for exit status expansion
//Returns size of exit status string
static size_t	handle_exit_status(int *i, t_mini *mini)
{
	char	*temp;
	size_t	size;

	size = 0;
	temp = ft_itoa(mini->exit_status);
	if (temp)
	{
		size = ft_strlen(temp);
		free(temp);
	}
	*i += 2;
	return (size);
}

//Calculates total size needed for expanded string
//Returns total size including null terminator
size_t	get_total_size(char *str, t_mini *mini)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (!i || str[i - 1] != '\\'))
			size += handle_quotes(str, &i, '\'');
		else if (str[i] == '\"' && (!i || str[i - 1] != '\\'))
			size += handle_quotes(str, &i, '\"');
		else if (str[i] == '$' && str[i + 1] == '?')
			size += handle_exit_status(&i, mini);
		else if (str[i] == '$' && str[i + 1] && !is_delimiter(str[i + 1]))
			size += get_env_len(str, &i);
		else
		{
			size++;
			i++;
		}
	}
	return (size + 1);
}

char	*env_var_expansion(char *str, t_mini *mini)
{
	char	*copy;
	size_t	size;

	if (!str)
		return (NULL);
	size = get_total_size(str, mini);
	copy = malloc(size * sizeof(char));
	if (!copy)
		return (NULL);
	ft_bzero(copy, size);
	return (process_env_vars(str, copy, mini));
}
