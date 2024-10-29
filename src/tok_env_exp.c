/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/28 18:32:22 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_env(char *str, int *i, t_mini *mini)
{
	int		start;
	int		len;
	char	*search;
	char	*result;

	if (!str || !i || !mini)
		return (NULL);
	start = ++(*i);
	if (str[*i] == '?')
	{
		result = ft_itoa(mini->exit_status);
		(*i)++;
		return (result);
	}
	while (str[*i] && !is_delimiter(str[*i]))
		(*i)++;
	len = *i - start;
	if (len <= 0)
		return (ft_strdup(""));
	search = ft_substr(str, start, len);
	if (!search)
		return (NULL);
	result = search_env(search, len, mini);
	free(search);
	return (result);
}

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

char	*env_var_expansion(char *str, t_mini *mini)
{
	char	*copy;
	size_t	alloc_size;

	if (!str || !mini)
	{
		ft_putstr_fd("null pointer in env_var_expansion\n", 2);
		return (NULL);
	}
	alloc_size = (ft_strlen(str) * 4 + 1);
	copy = malloc(alloc_size * sizeof(char));
	if (!copy)
	{
		ft_putstr_fd("malloc error in env_var_expansion\n", 2);
		return (NULL);
	}
	ft_bzero(copy, alloc_size);
	copy = process_env_vars(str, mini, copy);
	if (!copy)
		return (NULL);
	return (copy);
}