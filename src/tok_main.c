/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:52:18 by ttero             #+#    #+#             */
/*   Updated: 2024/10/29 23:43:04 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//makes substr of s from start to end
//adds substr to list with add_to_list
//returns 0 if malloc error, or if add_to_list fails
//returns 1 if successful
  static int	add_token(char *s, int start, int end, t_mini *mini)
{
	char	*token;

	if (!s || end < start)
		return (0);
	token = ft_substr(s, start, end - start);
	if (!token)
	{
		ft_putstr_fd("malloc error\n", 2);
		return (0);
	}
	if (!add_to_list(token, mini))
	{
		free(token);
		return (0);
	}
	free(token);
	return (1);
}

//adds delimiters as token to list
//checks if it's a single or double arrow
//returns 0 if malloc error, or if add_to_list fails
//returns 1 if successful
static int	handle_delimiter(char *s, int *i, t_mini *mini)
{
	char	delim[3];

	if (!s || !i || !mini)
		return (0);
	if (s[*i] == '>' || s[*i] == '<' || s[*i] == '|')
	{
		delim[0] = s[*i];
		delim[1] = '\0';
		delim[2] = '\0';
		if ((s[*i] == '>' || s[*i] == '<') && s[*i + 1] == s[*i])
		{
			delim[1] = s[*i];
			(*i)++;
		}
		if (!add_to_list(ft_strdup(delim), mini))
		{
			ft_putstr_fd("malloc error in handle_delimiter\n", 2);
			return (0);
		}
	}
	(*i)++;
	return (1);
}

//Process a single token from the input string
//Returns 0 on error, 1 on success
static int	process_token(char *s, int *i, int start, t_mini *mini)
{
	if (*i > start && !add_token(s, start, *i, mini))
		return (0);
	if (s[*i] && is_delimiter(s[*i]) && mini->status == DEFAULT
		&& !handle_delimiter(s, i, mini))
		return (0);
	return (1);
}

/*
int	add_token(char *s, int start, int end, t_mini *mini)
{
	char	*token;

	if (!s || end < start)
		return (0);
	token = ft_substr(s, start, end - start);
	if (!token)
	{
		ft_putstr_fd("malloc error\n", 2);
		return (0);
	}
	if (!add_to_list(token, mini))
	{
		free(token);
		return (0);
	}
	free(token);
	return (1);
}

//adds delimiters as token to list
//checks if it's a single or double arrow
//returns 0 if malloc error, or if add_to_list fails
//returns 1 if successful
static int	handle_delimiter(char *s, int *i, t_mini *mini)
{
	char	delim[3];

	if (!s || !i || !mini)
		return (0);
	if (s[*i] == '>' || s[*i] == '<' || s[*i] == '|')
	{
		delim[0] = s[*i];
		delim[1] = '\0';
		delim[2] = '\0';
		if ((s[*i] == '>' || s[*i] == '<') && s[*i + 1] == s[*i])
		{
			delim[1] = s[*i];
			(*i)++;
		}
		if (!add_to_list(ft_strdup(delim), mini))
		{
			ft_putstr_fd("malloc error in handle_delimiter\n", 2);
			return (0);
		}
	}
	(*i)++;
	return (1);
}

//sets start of token by skipping spaces
//increments i while s[i] is not a space or delimiter
//uses add_token to make substr given i and start, and add to mini->lst
//uses handle_delimiter to handle delimiters
//returns 0 if malloc error, or if add_token fails
//returns 1 if successful
int	token(char *s, t_mini *mini)
{
	int	i;
	int	start;

	if (!s || !mini)
		return (0);
	i = 0;
	start = 0;
	while (s[i])
	{
		skip_spaces(s, &i);
		start = i;
		while (s[i] && !(is_delimiter(s[i]) && mini->status == DEFAULT))
		{
			if (quotes(s, &i, mini) > 0)
				return (0);
			if (s[i] == '\0')
				break;
			i++;
		}
		if (i > start && !add_token(s, start, i, mini))
			return (0);
		if (s[i] && is_delimiter(s[i]) && mini->status == DEFAULT)
			if (!handle_delimiter(s, &i, mini))
				return (0);
	}
	return (1);
}


//Main tokenization function
//Splits input string into tokens based on delimiters and quotes
//Returns 0 on error, 1 on success
 int	token(char *s, t_mini *mini)
{
	int	i;
	int	start;

	if (!s || !mini)
		return (0);
	i = 0;
	while (s[i])
	{
		skip_spaces(s, &i);
		start = i;
		while (s[i] && !(is_delimiter(s[i]) && mini->status == DEFAULT))
		{
			if (quotes(s, &i, mini) == 1)
				return (0);
			if (!s[i])
				break ;
			printf("%d\n", i);
			i++;
		}
		if (!process_token(s, &i, start, mini))
			return (0);
	}
	return (1);
}
 */
/*  int add_to_list(char *k, t_mini *mini)
{
    t_token *new_token;
	char *copy;

	copy = strdup(k);
	new_token = ft_lstnew(copy);
    if (!new_token)
        return (0);
    ft_lstadd_back((mini->lst), *new_token);
    return (1);
} */

 static int	len_next(char *str, int i, t_mini mini)
{
	int	j;

	j = 0;
	skip_spaces(str, &i);
	//printf("%c\n", str[i]);
	while (str[i])
	{
		if (is_delimiter(str[i]) && mini.status == DEFAULT)
			{
				//printf("%d\n", j);
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

int token (char *s, t_mini *mini)
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
		if (is_delimiter(s[i]) && mini->status == DEFAULT)
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
	return (1);
}



//Takes input string and mini struct
//Expands environmental variables and tokenizes the input
//Returns 0 if malloc error or if expansion/tokenization fails
//Returns 1 if successful
 int	input_to_tokens(char *input, t_mini *mini)
{
	char	*expanded_input;

	if (!input || !mini)
		return (0);
	mini->lst = NULL;
	mini->status = DEFAULT;
	expanded_input = env_var_expansion(input, mini);
	//printf("%s\n", expanded_input);
	if (!expanded_input)
	{
		ft_putstr_fd("error expanding environmental variables\n", 2);
		return (0);
	}
	if (!token(expanded_input, mini))
	{
		free(expanded_input);
		return (0);
	}
	free(expanded_input);
	return (1);
}
