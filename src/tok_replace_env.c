/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_replace_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/25 10:07:13 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_mem(char *str, int add, int old)
{
	char *copy;

	copy	= strdup(str);
	free(str);
	str = malloc(old + add);
	str = strcpy(str, copy);
	free(copy);
	add = old + add;
	return (str);
}

char *get_env(char *str, int *i, char **env)
{
	char *search;
	int j;
	char *ret;
	int k;
	int z;

	j = 0;
	k = *i;
	k++;
	while (str[k] && isDelimiter(str[k]) == false)
	{
		k++;
		j++;
	}
	*i += j + 1;
	if (ft_isdigit(str[*i + 1]) == 1)
		return (strdup(""));
	search = malloc(j + 1);
	k -= j;
	j = 0;
	while (str[k] && isDelimiter(str[k]) == false)
	{
		search[j] = str[k];
		j++;
		k++;
	}
	search[j] = '\0';
	z = 0;
	while (env[z])
	{
		if (strncmp(env[z], search, j) == 0 && env[z][j] == '=')
			break;
		z++;
	}
	if (env[z] == NULL)
		return (strdup(""));
	ret = getenv(search);
	return (ret);
}

//handles variable expansion
//No expansion if single quotes
char *env_var_expansion(char *str, char **env, t_mini *mini)
{
	int i;
	int j;
	char *copy;
	size_t copy_size;
	char *env_var;
	size_t env_len;
	char *temp;

	i = 0;
	j = 0;
	copy_size = strlen(str) + 1;
	copy = malloc(copy_size);
	if (!copy)
		return NULL;
	while (str[i])
	{
		quotes(str, &i, mini);
		if (str[i] == '$' && mini->status != SINGLEQ)
		{
			env_var = get_env(str, &i, env);
			copy = add_mem(copy, strlen(env_var), copy_size);
			copy_size += strlen(env_var);
			ft_strlcat(copy + j, env_var, copy_size - j + 1);
			j += strlen(env_var);
		}
		else
		{
			copy[j] = str[i];
			j++;
			i++;
		}
	}
	copy[j] = '\0';
	if (mini->status != DEFAULT)
		printf("uneven quotes");
	return (copy);
}


