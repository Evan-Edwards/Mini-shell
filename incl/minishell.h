/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:28:04 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/24 16:14:48 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h> //errno
# include <fcntl.h>
# include "libft.h"
# include <readline/readline.h> //readline + rl_* functions
# include <readline/history.h> //readline + rl_* functions
# include <signal.h> //signal, sig* functions
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>


typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_mini
{
	int		status;
	t_token	*lst;
}					t_mini;

typedef enum e_status
{
	DEFAULT,
	SINGLEQ,
	DOUBLEQ,
}					t_status;

typedef enum e_type
{
	ARG,
	EMPTY,
	DASH,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
	PIPE,
}					t_type;

/* ************************************************************************** */
/*                              create_token                                  */
/* ************************************************************************** */
t_mini	ct_main(char *input);

int		quotes(char *s, int *i, t_mini *mini);
void	print_list(t_mini *mini);
int		add_to_list(char *k, t_mini *mini);
void	token(char *s, t_mini *mini);

/* ************************************************************************** */
/*                           create_token utils                               */
/* ************************************************************************** */
bool	isDelimiter(char ch);
bool	is_quotes(char ch);
void	skip_spaces(char *s, int *i);
void	ft_t_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_t_lstnew(void *content);

/* ************************************************************************** */
/*                              replace_env                                   */
/* ************************************************************************** */
char	*re_main(char *input, char **envp);

int		quotes2(char *s, int *i, t_mini mini);
char	*add_mem(char *str, int add, int old);
char	*add_end(char *dst, char *add, int j);
char	*get_env(char *str, int *i, char **env);
char	*first_check(char *str, char **env, t_mini mini);

/* ************************************************************************** */
/*                                SIGNALS                                     */
/* ************************************************************************** */
void	ft_signal_setup(void);

/* ************************************************************************** */
/*                              EXECUTE PWD                                   */
/* ************************************************************************** */
char	*get_current_directory(void);
int		ft_pwd(void);

/* ************************************************************************** */
/*                              EXECUTE CD                                    */
/* ************************************************************************** */
char	*rm_last_dir(char *cwd);
int		ft_cd(char *path);
char	*mod_cwd(char *cwd, char *path);

/* ************************************************************************** */
/*                             EXECUTE EXPORT                                 */
/* ************************************************************************** */
int		count_env_variables(char **envp);
int		ft_export_no_arg(char **envp);
char	**sort_array(char **to_sort, int iterations);
char	**copy_str_array(char	**orig, char **copy);
void	free_str_array(char **to_free);
void	print_env(char *env);

/* ************************************************************************** */
/*                             EXECUTE UNSET                                  */
/* ************************************************************************** */
int		ft_unset(char **envp, char **to_unset);
void	remove_str_from_array(char ***envp, int *j);

/* ************************************************************************** */
/*                              EXECUTE ENV                                   */
/* ************************************************************************** */
int	ft_env(char **envp)

/* ************************************************************************** */
/*                             CLOSE PROGRAM                                  */
/* ************************************************************************** */
void	ft_error_close(char *error_message);
void	ft_close(void);
void	ft_perror_close(char *perror_message);

#endif
