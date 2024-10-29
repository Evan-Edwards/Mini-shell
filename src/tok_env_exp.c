/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/29 12:44:55 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Forward declaration at the top of the file
static int handle_dollar(char *str, int *i, char *copy, int *j, t_mini *mini);

//Copies content between quotes, excluding the quotes themselves
//Updates indices to track position in input and output strings
static void	copy_quoted(char *str, int *i, char *copy, int *j, t_mini *mini)
{
	char quote_type;

	quote_type = str[*i];
	if (quote_type == '"')  // For double quotes, keep processing env vars
	{
		(*i)++;  // Skip opening quote
		while (str[*i] && str[*i] != quote_type)
		{
			if (str[*i] == '$')
			{
				if (!handle_dollar(str, i, copy, j, mini))
					return;
			}
			else
			{
				copy[*j] = str[*i];
				(*i)++;
				(*j)++;
			}
		}
	}
	else  // For single quotes, copy everything literally
	{
		(*i)++;  // Skip opening quote
		while (str[*i] && str[*i] != quote_type)
		{
			copy[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
	}
	if (str[*i] == quote_type)
		(*i)++;  // Skip closing quote
}

//Gets value of environment variable or exit status
//Returns malloc'd string containing value or NULL on error
static char	*get_env_value(char *str, int *i, t_mini *mini)
{
	int		start;
	char	*var_name;
	char	*env_val;
	char	*result;

	start = ++(*i);  // Skip the $
	// Handle $? first
	if (str[start] == '?')
	{
		(*i)++;  // Move past the ?
		return (ft_itoa(mini->exit_status));
	}
	if (!str[start] || is_delimiter(str[start]))
	{
		(*i)--;  // Move back to $ position
		return (ft_strdup("$"));
	}
	while (str[*i] && !is_delimiter(str[*i]))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (NULL);
	env_val = getenv(var_name);
	free(var_name);
	if (!env_val)
		return (ft_strdup(""));
	result = ft_strdup(env_val);
	return (result);
}

//Handles expansion of environment variables and $ symbol
//Returns 1 on success, 0 on error
static int	handle_dollar(char *str, int *i, char *copy, int *j, t_mini *mini)
{
	char	*env_val;
	size_t	val_len;

	// Handle single $ case directly
	if (!str[*i + 1] || str[*i + 1] == '"' || str[*i + 1] == '\'' || is_delimiter(str[*i + 1]))
	{
		copy[*j] = '$';
		(*i)++;
		(*j)++;
		return (1);
	}

	env_val = get_env_value(str, i, mini);
	if (!env_val)
		return (0);
	val_len = ft_strlen(env_val);
	ft_strlcpy(copy + *j, env_val, val_len + 1);
	*j += val_len;
	free(env_val);
	return (1);
}

//Main function to process environment variables and quotes
//Returns processed string or NULL on error
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
		else if ((str[i] == '\'' || str[i] == '\"') && mini->status == DEFAULT)
			copy_quoted(str, &i, copy, &j, mini);
		else
		{
			copy[j++] = str[i++];
		}
	}
	copy[j] = '\0';
	return (copy);
}

//Entry point for environment variable expansion
//Returns expanded string or NULL on error
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