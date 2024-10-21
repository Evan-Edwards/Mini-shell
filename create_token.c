/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:18 by ttero             #+#    #+#             */
/*   Updated: 2024/10/21 11:51:27 by eedwards         ###   ########.fr       */
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
		}
        if (is_quotes(s, i) == 1)
            quotes(s, i, mini);
		return (1);
	}
	return (0);
}

static int	len_next(char *str, int i, t_mini mini)
{
	int	j;

	j = 0;
	skip_spaces(str, &i);
	//printf("%c\n", str[i]);
	while (str[i] && mini.status == DEFAULT && isDelimiter(str[i]) == false)
	{
		quotes(str, &i, mini);
		i++;
		j++;
	}
	//j++;
	return (j);
}
void	print_list(t_mini *mini)
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

void	token (char *s, t_mini *mini)
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
        quotes(s, &i, *mini);
        k[j] = s[i];
        j++;
		if (isDelimiter(s[i]))
			{
                k[j] = '\0';
				add_to_list(k, mini);
                free (k);
                malloc_flag = 0;
                j = 0;
            }
        i++;
	}
	k[j] = '\0';
	add_to_list(k, mini);
    free (k);
}


t_mini	ct_main(char *input)
{
	char *res;
	t_mini mini;
	t_mini mini2;

	mini.lst = NULL;
	mini2.lst = NULL;
	mini.status = DEFAULT;
	token(input, &mini);
	return (mini);
	//print_list(&mini);
    //return 0;
	//return (1);
}
//error handling?




