/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_quote_proc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/28 18:39:20 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_quoted_content(char *str, int *i, char **copy, char quote);
static int	handle_dollar_sign(char *str, int *i, char **copy, t_mini *mini);

char	*process_env_vars(char *str, t_mini *mini, char *copy)
{
	int		i;
	int		j;
	char	quote;
	int		ret;

	if (!str || !mini || !copy)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			ret = process_quoted_content(str, &i, &copy, quote);
			if (ret == 0)
				return (NULL);
			if (ret == 2 && !handle_dollar_sign(str, &i, &copy, mini))
				return (NULL);
			if (str[i])
				i++;
			continue ;
		}
		if (str[i] == '$' && !handle_dollar_sign(str, &i, &copy, mini))
			return (NULL);
		else if (str[i] != '$')
			copy[j++] = str[i++];
	}
	copy[j] = '\0';
	return (copy);
}

static int	handle_dollar_sign(char *str, int *i, char **copy, t_mini *mini)
{
	char	*env_var;
	size_t	new_size;
	int		j;

	j = ft_strlen(*copy);
	env_var = get_env(str, i, mini);
	if (!env_var)
		return (0);
	new_size = j + ft_strlen(env_var) + ft_strlen(str + *i) + 1;
	*copy = add_copy_size(*copy, new_size);
	if (!*copy)
	{
		free(env_var);
		return (0);
	}
	ft_strlcat(*copy + j, env_var, new_size - j);
	free(env_var);
	return (1);
}
