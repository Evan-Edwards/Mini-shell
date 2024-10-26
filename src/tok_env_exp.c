/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/26 11:52:08 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reallocates memory for the copy string if needed
// Returns the new (or unchanged) copy string
static char	*add_copy_size(char *copy, size_t new_total_size)
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


//iterates through the env array to find a matching environment variable
//compares the start of each env string (until '=') with the search string
//if a match is found, uses getenv to retrieve the variable's value
//returns a newly allocated string containing the value or an empty string
//if no match is found, returns an empty string
static char	*search_env(char *search, int len, char **env)
{
	int		j;
	char	*ret;
	char	*result;

	j = 0;
	while (env[j])
	{
		if (strncmp(env[j], search, len) == 0 && env[j][len] == '=')
		{
			ret = getenv(search);
			if (ret)
				result = ft_strdup(ret);
			else
				result = ft_strdup("");
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

//finds length of env variable name in input str
//allocates memory for copy and copies variable name
//searches env array for matching variable with search_env
//if found returns value of variable by recalling getenv
char	*get_env(char *str, int *i, char **env)
{
	int		start;
	int		len;
	char	*search;
	char	*result;

	start = ++(*i);
	while (str[*i] && !is_delimiter(str[*i]))
		(*i)++;
	len = *i - start;
	if (ft_isdigit(str[start]))
		return (ft_strdup(""));
	search = ft_substr(str, start, len);
	if (!search)
		return (NULL);
	result = search_env(search, len, env);
	free(search);
	return (result);
}

//handles expansion of a single environment variable
//gets the env var value, resizes the copy buffer if needed
//adds the expanded value to the copy string
//returns the updated copy string or NULL on error
static char *handle_env_var(char *str, int *i, char **env, char **copy)
{
	char	*env_var;
	size_t	new_size;
	int		j;
	
	j = ft_strlen(*copy);
	env_var = get_env(str, i, env);
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

//iterates through str, expanding environment variables
//checks for quotes using quotes function
//expands $ variables outside single quotes using handle_env_var
//copies other characters to copy string
//returns the fully processed copy string or NULL on error
static char *process_env_vars(char *str, char **env, t_mini *mini, char *copy)
{
	int i = 0;
	int j = 0;

	while (str[i])
	{
		quotes(str, &i, mini);
		if (str[i] == '$' && mini->status != SINGLEQ)
		{
			if (!handle_env_var(str, &i, env, &copy))
				return (NULL);
			j = ft_strlen(copy);
		}
		else
			copy[j++] = str[i++];
	}
	copy[j] = '\0';
	return (copy);
}

//allocates room for expanded copy of str
//uses process_env_vars to expand env variables
//null-terminates copy string
//if there was starting but not ending quote 
char	*env_var_expansion(char *str, char **env, t_mini *mini)
{
	char	*copy;

	copy = malloc(strlen(str) + 1);
	if (!copy)
		return (NULL);
	copy = process_env_vars(str, env, mini, copy);
	if (!copy)
		return (NULL);
	if (mini->status != DEFAULT)
		ft_putstr_fd("uneven quotes", 2);
	return (copy);
}
