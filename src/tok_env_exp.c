/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/25 13:32:38 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//iterates through str
//checks for quotes using quotes
//expands $ variables outside single quotes using get_env
//Then resizes the copy buffer if needed and adds value to copy string
//copies other character to copy str
static char	*process_env_vars(char *str, char **env, t_mini *mini, char *copy)
{
	int		i;
	int		j;
	char	*env_var;

	i = 0;
	j = 0;
	while (str[i])
	{
		quotes(str, &i, mini);
		if (str[i] == '$' && mini->status != SINGLEQ)
		{
			env_var = get_env(str, &i, env);
			if (env_var == NULL)
				return (NULL);
			copy = add_copy_size(copy, ft_strlen(env_var),
					j + ft_strlen(env_var) + 1);
			ft_strlcat(copy + j, env_var, j + strlen(env_var) + 1);
			j += ft_strlen(env_var);
			free(env_var);
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
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	copy = malloc(strlen(str) + 1);
	if (!copy)
		return (NULL);
	copy = process_env_vars(str, env, mini, copy);
	if (!copy)
		return (NULL);
	copy[j] = '\0';
	if (mini->status != DEFAULT)
		printf("uneven quotes");
	return (copy);
}
