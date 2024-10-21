/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:11 by ttero             #+#    #+#             */
/*   Updated: 2024/10/21 20:01:42 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quotes2(char *s, int *i, t_mini mini)
{
	if (s[*i] == '\'')
	{
		if (mini.status == DEFAULT)
			mini.status = SINGLEQ;
		else if (mini.status == SINGLEQ)
			mini.status = DEFAULT;
		else
		{
			return (1);
		}
		return (1);
	}
	if (s[*i] == '\"')
	{
		if (mini.status == DEFAULT)
		{
			mini.status = DOUBLEQ;
		}
		else if (mini.status == DOUBLEQ)
		{
			mini.status = DEFAULT;
		}
		else
		{
			return (1);
		}
		return (1);
	}
	return (0);
}




char  *add_mem (char *str, int add, int old)
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

char *add_end (char *dst, char *add, int j)
{
    int i;

    i = 0;
    //j++;
	//printf("%s\n", add);
	//printf("%s\n", copy);
    while (add[i])
    {
        dst[j] = add[i];
        j++;
        i++;
    }
	dst[j] = '\0';
	//printf("%s\n", dst);
    return (dst);
}

char *get_env (char *str, int *i, char **env)
{
    char *search;
    int j;
    char *ret;
    int k;
    int z;

	//return (strdup(""));
    j = 0;
    k = *i;
    k++;
    while(str[k] && isDelimiter(str[k]) == false)
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
    while(str[k] && isDelimiter(str[k]) == false)
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
    //ret = strchr(env[z], '=');
    return (ret);

}


char *first_check(char *str, char **env,  t_mini mini)
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
	//printf("%d\n", mem);
	//return (NULL);
    copy = malloc(mem + 1);
	//return (NULL);
	//return (NULL);
    while (str[i])
    {
        quotes2(str, &i, mini);
        if (str[i] == '$' && mini.status != SINGLEQ)
        {
			env_var = get_env(str, &i, env);
			//printf("%s\n", env_var);
            //printf("%d\n", i);
			//return (NULL);
            copy = add_mem(copy, strlen(env_var), mem);
			//return (NULL);
            mem += strlen(env_var);
            copy = add_end(copy, env_var, j);
            //free (env1);
			//return (copy);
            //i += strlen(env_var);   //fix
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
