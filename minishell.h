/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:28:04 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/21 11:51:18 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI-SHELL_H
# define MINI-SHELL_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft/incl/libft.h"
#include <readline/readline.h> //readline + rl_* functions
#include <readline/history.h> //readline + rl_* functions


typedef struct	s_token
{
	char			*content;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_mini
{
    int     status;
	t_token	*lst;
}					t_mini;

typedef enum e_status
{
	DEFAULT,
	SINGLEQ,
	DOUBLEQ,
}					t_status;

/* ************************************************************************** */
/*                              create_token                                  */
/* ************************************************************************** */
t_mini	ct_main(char *input);

int		quotes(char *s, int *i, t_mini mini);
void	print_list(t_mini *mini);
void	token (char *s, t_mini *mini);

/* ************************************************************************** */
/*                           create_token utils                               */
/* ************************************************************************** */
bool	isDelimiter(char ch);
int		is_seperator (char* sep, char c);
int		is_quotes (char *s, int *i);
void	skip_spaces (char *s, int *i);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstnew(void *content);
int		add_to_list(char *k, t_mini *mini);

/* ************************************************************************** */
/*                              replace_env                                   */
/* ************************************************************************** */
int		re_main(int argc, char *argv[], char **envp);

bool	isDelimiter(char ch);
int		is_quotes(char *s, int *i);
int		quotes(char *s, int *i, t_mini mini);
char	*add_mem(char *str, int add, int old);
char	*add_end(char *dst, char *add, int j);
char	*get_env(char *str, int i, char **env);
char	*first_check(char *str, char **env,  t_mini mini);

#endif