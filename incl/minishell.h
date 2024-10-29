/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:28:04 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 12:47:39 by ttero            ###   ########.fr       */
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

typedef struct s_history
{
	char	**commands;
	int		capacity;
	int		count;
}					t_history;

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_mini
{
	int				flag;
	int				in;
	int				out;
	int				ret_value;
	int				status;
	int				exit_status;
	char			**envp;
	t_token			*lst;
	t_history		*history;
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
	PIPE,
	INPUT,
	HEREDOC,
	OUTPUT,
	APPEND,
	EXTRA,
}					t_type;

/* ************************************************************************** */
/*                              create_token                                  */
/* ************************************************************************** */
int		input_to_tokens(char *input, t_mini *mini);
int		token(char *s, t_mini *mini);
char	*env_var_expansion(char *str, t_mini *mini);

/* ************************************************************************** */
/*                           create token utils                               */
/* ************************************************************************** */
bool	is_delimiter(char ch);
bool	is_quotes(char ch);
void	skip_spaces(char *s, int *i);
int		quotes(char *s, int *i, t_mini *mini);
char	*add_mem(char *str, int add, int old);
char	*add_end(char *dst, char *add, int j);
char	*get_env(char *str, int *i, t_mini *mini);
char	*add_copy_size(char *copy, size_t new_total_size);

/* ************************************************************************** */
/*                          token list utils                                  */
/* ************************************************************************** */
int		add_to_list(char *k, t_mini *mini);
void	ft_t_lstadd_back(t_token **lst, t_token *new);
void	print_list(t_mini *mini);
t_token	*ft_t_lstnew(char *content);

/* ************************************************************************** */
/*                              HISTORY                                      */
/* ************************************************************************** */
int		ft_history(char *command, t_mini *mini);
int		init_history(t_history **history);
int		add_to_history(t_history *history, char *command);
int		clear_history_contents(t_history *history);
int		print_history(t_history *history);
int		ex_history(char **arg, t_history *history);

/* ************************************************************************** */
/*                                SIGNALS                                     */
/* ************************************************************************** */
void	ft_signal_setup(void);

/* ************************************************************************** */
/*                              EXECUTE ECHO                                  */
/* ************************************************************************** */
int		ft_echo(char **command);

/* ************************************************************************** */
/*                              EXECUTE PWD                                   */
/* ************************************************************************** */
char	*get_current_directory(void);
int		ft_pwd(void);

/* ************************************************************************** */
/*                              EXECUTE CD                                    */
/* ************************************************************************** */
char	*rm_last_dir(char *cwd);
int		ft_cd(char **arg);
char	*mod_cwd(char *cwd, char *path);

/* ************************************************************************** */
/*                             EXECUTE EXPORT                                 */
/* ************************************************************************** */
int		count_env_variables(char **envp);
int		export_no_arg(char **envp);
int		export_with_arg(char **command, t_mini *mini);
int		find_env_index(char *name, t_mini *mini);
char	**sort_array(char **to_sort, int iterations);
char	**copy_str_array(char	**orig, char **copy);
void	print_env(char *env);
int		validate_name(char **command, int *i);
int		ft_export(char **command, t_mini *mini);

/* ************************************************************************** */
/*                             EXECUTE UNSET                                  */
/* ************************************************************************** */
int		ft_unset(char **envp, char **to_unset);
void	remove_str_from_array(char ***envp, int *j);

/* ************************************************************************** */
/*                              EXECUTE ENV                                   */
/* ************************************************************************** */
int		ft_env(char **envp);

/* ************************************************************************** */
/*                              EXECUTE EXIT                                  */
/* ************************************************************************** */
void	ft_exit(char **command, t_mini *mini);

/* ************************************************************************** */
/*                             CLOSE PROGRAM                                  */
/* ************************************************************************** */
void	ft_close(int exit_status, char *input, char **arg, t_mini *mini);

/* ************************************************************************** */
/*                                FREE                                      */
/* ************************************************************************** */
void	free_mini(t_mini *mini);
void	free_str_array(char **to_free);
void	clear_t_history(t_mini *mini);
void	free_list(t_token *lst);
void	reset_input(char *input, t_mini *mini);

/* ************************************************************************** */
/*                             DISTRIBUTE                                     */
/* ************************************************************************** */
int		builtin(char **arg, t_mini *mini);
int		distribute(t_mini *mini, t_token *current);
int		number_of_arguments(t_token *lst);
int		is_builtin(char *arg);
char	**build_exe(t_token *lst);
void	execute_command(char **arg, t_mini *mini);
void	print_array(char **arg);
char	*get_path(char *argv, char **envp);
char	*get_path2(char *argv, char **envp);
int		is_env(char *env[]);
char	*find_path(char *argv, char *env[]);
int		dis_b(t_mini *mini);
int		exe(char **arg, t_mini *mini);

/* ************************************************************************** */
/*                             FILE HANDLING                                  */
/* ************************************************************************** */
int		file_in(t_token *lst);
int		file_out(t_token *lst);
int		input_file(int type, char *file_name);
int		output_file(int type, char *file_name);

/* ************************************************************************** */
/*                             SET TYPES                                      */
/* ************************************************************************** */
int		count_pipes(t_token *lst);
int		set_types(t_token *lst);
int		reg(char *str);
int		check_errors(t_token *lst);

int	validate_command_path(char **arg, t_mini *mini, char **path);
int	create_pipe(int pipe_fd[2]);

#endif
