/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/28 11:01:04 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//iterates through the env array to find a matching environment variable
//compares the start of each env string (until '=') with the search string
//if a match is found, uses getenv to retrieve the variable's value
//returns a newly allocated string containing the value or an empty string
//if no match is found, returns an empty string
static char	*search_env(char *search, int len, t_mini *mini)
{
	int		j;
	char	*result;
	char	*env_value;

	if (!search || !mini || !mini->envp || len < 0)
		return (NULL);
	j = 0;
	while (mini->envp[j])
	{
		if (strncmp(mini->envp[j], search, len) == 0
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
		ft_putstr_fd("malloc error\n", 2);
	return (result);
}

//finds length of env variable name in input str
//allocates memory for copy and copies variable name
//searches env array for matching variable with search_env
//if found returns value of variable by recalling getenv
char	*get_env(char *str, int *i, t_mini *mini)
{
	int		start;
	int		len;
	char	*search;
	char	*result;

	if (!str || !i || !mini)
		return (NULL);
	start = ++(*i);
	while (str[*i] && !is_delimiter(str[*i]))
		(*i)++;
	len = *i - start;
	if (len <= 0 || ft_isdigit(str[start]))
		return (ft_strdup(""));
	search = ft_substr(str, start, len);
	if (!search)
		return (NULL);
	result = search_env(search, len, mini);
	free(search);
	return (result);
}

//handles expansion of a single environment variable
//gets the env var value, resizes the copy buffer if needed
//adds the expanded value to the copy string
//returns the updated copy string or NULL on error
static char	*handle_env_var(char *str, int *i, t_mini *mini, char **copy)
{
	char	*env_var;
	size_t	new_size;
	int		j;

	if (!str || !i || !mini || !copy || !*copy)
		return (NULL);
	j = ft_strlen(*copy);
	env_var = get_env(str, i, mini);
	if (!env_var)
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
static char	*process_env_vars(char *str, t_mini *mini, char *copy)
{
	int	i;
	int	j;

	if (!str || !mini || !copy)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		quotes(str, &i, mini);
		if (str[i] == '$' && mini->status != SINGLEQ)
		{
			if (!handle_env_var(str, &i, mini, &copy))
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
char	*env_var_expansion(char *str, t_mini *mini)
{
	char	*copy;

	if (!str || !mini)
	{
		ft_putstr_fd("null pointer in env_var_expansion\n", 2);
		return (NULL);
	}
	copy = malloc(ft_strlen(str) + 1);
	if (!copy)
	{
		ft_putstr_fd("malloc error in env_var_expansion\n", 2);
		return (NULL);
	}
	copy = process_env_vars(str, mini, copy);
	if (!copy)
		return (NULL);
	if (mini->status != DEFAULT)
	{
		ft_putstr_fd("uneven quotes\n", 2);
		free(copy);
		return (NULL);
	}
	return (copy);
}
