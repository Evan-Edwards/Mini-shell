/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/21 13:14:12 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes(char *s, int *i, t_mini mini)
{
	if (s[*i] == '\'')
	{
		if (mini.status == DEFAULT)
		{
			mini.status == SINGLEQ;
			*i ++;
		}
		else if (mini.status == SINGLEQ)
		{
			mini.status == DEFAULT;
			*i ++;
		}
		else
		{
			return (1);
			//mini.status[0] == s[*i];
			//i++;
		}
		if (is_quotes(s, i) == 1)
			quotes(s, i, mini);
		return (1);
	}
	if (s[*i] == '\"')
	{
		if (mini.status == DEFAULT)
		{
			mini.status == DOUBLEQ;
			*i ++;
		}
		else if (mini.status == DOUBLEQ)
		{
			mini.status == DEFAULT;
			*i ++;
		}
		else
		{
			return (1);
			//mini.token[0] == s[*i];
			//i++;
		}
		if (is_quotes(s, i) == 1)
			quotes(s, i, mini);
		return (1);
	}
	return (0);
}

char	*add_mem(char *str, int add, int old)
{
	char *copy;

	copy  = strdup(str);
	free(str);
	str = malloc(old + add);
	str = strcpy(str, copy);
	free (copy);
	add = old + add;
	return (str);
}

char	*add_end(char *dst, char *add, int j)
{
	int i;

	i = 0;
	//j++;
	printf("%s\n", add);
	//printf("%s\n", copy);
	while (add[i])
	{
		dst[j] = add[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	printf("%s\n", dst);
	return (dst);
}

char	*get_env(char *str, int i, char **env)
{
	char *search;
	int j;
	char *ret;

	//return (strdup(""));
	if (ft_isdigit(str[i + 1]) == 1)
		return (strdup(""));
	j = 0;
	i++;
	//return (strdup(""));
	while(str[i] && isDelimiter(str[i]) == false)
	{
		i++;
		j++;
	}
	//return (strdup(""));
	search = malloc(j + 1);
	i -= j;
	j = 0;
	while(str[i] && isDelimiter(str[i]) == false)
	{
		search[j] = str[i];
		j++;
		i++;
	}
	search[j] = '\0';
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], search, j) == 0 && env[i][j] == '=')
			break;
		i++;
	}
	if (env[i] == NULL)
		return (strdup(""));
	ret = strchr(env[i], '=');
	return (ret);

}



char	*first_check(char *str, char **env,  t_mini mini)
{
	int i;
	char *env_var;
	char *copy;
	int j;
	int mem;
	//t_mini mini;


	i = 0;
	j = 0;
	mem = strlen(str);
	printf("%d\n", mem);
	//return (NULL);
	copy = malloc(mem + 1);
	//return (NULL);
	//return (NULL);
	while (str[i])
	{
		quotes(str, &i, mini);
		if (str[i] == '$' && mini.status != SINGLEQ)
		{
			env_var = get_env(str, i, env);
			//printf("%s\n", env1);
			//return (NULL);
			copy = add_mem(copy, strlen(env_var), mem);
			//return (NULL);
			mem += strlen(env_var);
			copy = add_end(copy, env_var, j);
			//free (env1);
			return (copy);
			i += strlen(env_var);   //fix
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
	if (mini.status != DEFAULT)
		printf("uneven quotes");
	return (copy);
}


char *re_main(char *input, char **envp);
{
	char *res;
	t_mini mini;

	res = first_check(input, envp, mini);
	printf(" %s\n", res);

	return (res);
    //return (1);
}
