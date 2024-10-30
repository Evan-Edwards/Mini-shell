/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/30 22:41:19 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//iterates through the env array to find a matching environment variable
//compares the start of each env string (until '=') with the search string
//if a match is found, uses getenv to retrieve the variable's value
//returns a newly allocated string containing the value or an empty string
//if no match is found, returns an empty string
char	*search_env(char *search, int len, t_mini *mini)
{
	int		j;
	char	*result;
	char	*env_value;

	j = 0;
	while (mini->envp[j])
	{
		if (ft_strncmp(mini->envp[j], search, len) == 0
			&& mini->envp[j][len] == '=')
		{
			env_value = mini->envp[j] + len + 1;
			result = ft_strdup(env_value);
			if (!result)
				return (NULL);
			return (result);
		}
		j++;
	}
	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (result);
}

//handles expansion of a single environment variable
//gets the env var value, resizes the copy buffer if needed
//adds the expanded value to the copy string
//returns the updated copy string or NULL on error
char	*handle_env_var(char *str, int *i, t_mini *mini, char **copy)
{
	char	*env_var;
	size_t	new_size;
	int		j;

	j = ft_strlen(*copy);
	env_var = get_env(str, i, mini);
	if (env_var == NULL)
		return (NULL);
	new_size = j + ft_strlen(env_var) + ft_strlen(str + *i) + 1;
	*copy = add_copy_size(*copy, new_size);
	if (!*copy)
	{
		free(env_var);
		return (NULL);
	}
	ft_strlcat(*copy + j, env_var, new_size - j);
	free(env_var);
	return (*copy);
}

// Updates quote status based on current character
// Handles both single and double quotes
// Returns 1 if quote was found, 0 otherwise
// Updates mini->status based on quote type
int	quotes2(char *s, int *i, t_mini *mini)
{
	if (s[*i] == '\'')
	{
		if (mini->status == DEFAULT)
			mini->status = SINGLEQ;
		else if (mini->status == SINGLEQ)
			mini->status = DEFAULT;
		else
			return (1);
		return (1);
	}
	if (s[*i] == '\"')
	{
		if (mini->status == DEFAULT)
			mini->status = DOUBLEQ;
		else if (mini->status == DOUBLEQ)
			mini->status = DEFAULT;
		else
			return (1);
		return (1);
	}
	return (0);
}

//iterates through str, expanding environment variables
//checks for quotes using quotes function
//expands $ variables outside single quotes using handle_env_var
//copies other characters to copy string
//returns the fully processed copy string or NULL on error
char	*process_env_vars(char *str, t_mini *mini, char *copy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		quotes2(str, &i, mini);
		if (str[i] == '$' && mini->status != SINGLEQ)
		{
			if (!str[i + 1] || is_delimiter(str[i + 1])
				|| is_quotes(str[i + 1]))
			{
				copy[j++] = str[i++];
				continue ;
			}
			if (!handle_env_var(str, &i, mini, &copy))
				return (NULL);
			j = ft_strlen(copy);
		}
		else if (str[i])
			copy[j++] = str[i++];
	}
	copy[j] = '\0';
	return (copy);
}

//allocates room for expanded copy of str
//uses process_env_vars to expand env variables
//null-terminates copy string
//if there was starting but not ending quote
char	*env_var_expansion(char *str, t_mini *mini)
{
	char	*copy;

	copy = ft_calloc(ft_strlen(str) + 1, 1);
	if (!copy)
		return (NULL);
	copy = process_env_vars(str, mini, copy);
	if (!copy)
		return (NULL);
	if (mini->status != DEFAULT)
	{
		ft_putstr_fd("uneven quotes\n", 2);
		free (copy);
		return (NULL);
	}
	return (copy);
}
