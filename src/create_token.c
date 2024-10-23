/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:18 by ttero             #+#    #+#             */
/*   Updated: 2024/10/23 20:27:56 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quotes(char *s, int *i, t_mini *mini)
{
	if (s[*i] == '\'')
	{
		if (mini->status == DEFAULT)
		{
			mini->status = SINGLEQ;
			*i = *i +1;
		}
		else if (mini->status == SINGLEQ)
		{
			mini->status = DEFAULT;
			*i = *i +1;
		}
		else
		{
			return (1);
		}
        if (is_quotes(s[*i]) == true)
            quotes(s, i, mini);
		return (1);
	}
	if (s[*i] == '\"')
	{
		if (mini->status == DEFAULT)
		{
			mini->status = DOUBLEQ;
			*i = *i +1;
		}
		else if (mini->status == DOUBLEQ)
		{
			mini->status = DEFAULT;
			*i = *i +1;
		}
		else
		{
			return (1);
		}
        if (is_quotes(s[*i]) == true)
            quotes(s, i, mini);
		return (1);
	}
	return (0);
}


void print_list(t_mini *mini)
{
    t_token *current = mini->lst;

	if (mini->lst == NULL)
    {
        printf("The list is empty.\n");
        return;
    }
    while (current != NULL)
    {
		printf("%s\n", current->content);
        current = current->next;
    }
}



int add_to_list(char *k, t_mini *mini)
{
    t_token *new_token;
	char *copy;

	copy = strdup(k);
	new_token = ft_t_lstnew(copy);
    if (!new_token)
        return (0);
    ft_t_lstadd_back(&(mini->lst), new_token);
    return (1);
}

static int	len_next(char *str, int i, t_mini mini)
{
	int	j;

	j = 0;
	skip_spaces(str, &i);
	while (str[i])
	{
		if (isDelimiter(str[i]) && mini.status == DEFAULT)
			{
				printf("%d\n", j);
				break;
			}
		quotes(str, &i, &mini);
		if (str[i] == '\0')
			break;
		i++;
		j++;
	}
	return (j);
}

int check_sep(char *s, int *i, t_mini *mini)
{
	char *k;

	if (s[*i] == '>')
	{
		if (s[*i+1] == '>')
		{
			if (!(k = malloc(3)))
        		printf("malloc error");
			k[0] = s[*i];
			k[1] = s[*i];
			k[2] = '\0';
			add_to_list(k, mini);
			*i += 1;
		}
		else
		{
			if (!(k = malloc(2)))
        		printf("malloc error");
			k[0] = s[*i];
			k[1] = '\0';
			add_to_list(k, mini);
		}
		free (k);
	}
	else if (s[*i] == '<')
	{
		if (s[*i+1] == '<')
		{
			if (!(k = malloc(3)))
        		printf("malloc error");
			k[0] = s[*i];
			k[1] = s[*i];
			k[2] = '\0';
			add_to_list(k, mini);
			*i += 1;
		}
		else
		{
			if (!(k = malloc(2)))
        		printf("malloc error");
			k[0] = s[*i];
			k[1] = '\0';
			add_to_list(k, mini);
		}
		free (k);
	}
	else
	{
		if (!(k = malloc(2)))
        	printf("malloc error");
			k[0] = s[*i];
			k[1] = '\0';
			add_to_list(k, mini);
	}
	return (1);
}

void token (char *s, t_mini *mini)
{
	int i;
	int j;
    int len;
    int malloc_flag;
    char *k;

	i = 0;
    j = 0;
    malloc_flag = 0;
	while(s[i])
	{
		if (malloc_flag == 0)
        {
            skip_spaces(s, &i);
            len = len_next(s, i, *mini);
            if (!(k = malloc(len + 1)))
                printf("malloc error");
            malloc_flag = 1;
        }
        quotes(s, &i, mini);
		if (s[i] == '\0')
			break;
		if (isDelimiter(s[i]) && mini->status == DEFAULT)
			{
				k[j] = '\0';
				if (strlen(k) > 0)
					add_to_list(k, mini);
                free (k);
				if (s[i] == '>' || s[i] == '<' || s[i] == '|')
					check_sep(s, &i, mini);
                malloc_flag = 0;
                j = 0;
            }
		 else
		{
			k[j] = s[i];
			 j++;
		}
        i++;
	}
	k[j] = '\0';
	add_to_list(k, mini);
    free (k);
}


t_mini	ct_main(char *input)
{
	//char *res;
	t_mini mini;
	//t_mini mini2;

	mini.lst = NULL;
	//mini2.lst = NULL;
	mini.status = DEFAULT;
	token(input, &mini);
	//print_list(&mini);
	return (mini);
}
//error handling?




