/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_get_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:09:10 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 11:09:16 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Handles exit status variable
static char	*handle_exit_status(int *i, t_mini *mini)
{
	(*i)++;
	return (ft_itoa(mini->exit_status));
}

//Gets length of environment variable name
static int	get_env_len(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && !is_delimiter(str[*i]) && !is_quotes(str[*i]))
		(*i)++;
	return (*i - start);
}

//Creates and searches for environment variable
static char	*search_env_var(char *str, int start, int len, t_mini *mini)
{
	char	*search;
	char	*result;

	if (ft_isdigit(str[start]))
		return (ft_strdup(""));
	search = ft_substr(str, start, len);
	if (!search)
		return (NULL);
	result = search_env(search, len, mini);
	free(search);
	return (result);
}

//Main environment variable handling function
char	*get_env(char *str, int *i, t_mini *mini)
{
	int		start;
	int		j;
	char	*result;

	j = *i;
	start = ++(*i);
	if (str[start] == '?')
		return (handle_exit_status(i, mini));
	result = search_env_var(str, start, get_env_len(str, i), mini);
	if (!result)
		*i = j;
	return (result);
}