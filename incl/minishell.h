/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:28:04 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 22:08:20 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h> //errno
# include <sys/ioctl.h> //ioctl
# include "libft.h"
# include <readline/readline.h> //readline + rl_* functions
# include <readline/history.h> //readline + rl_* functions
# include <signal.h> //signal, sig* functions
# include <stdbool.h> //bool
# include <stdlib.h> //malloc, free, exit, getenv
# include <string.h> //strerror
# include <sys/wait.h> //waitpid
# include <unistd.h> //chdir, fork, dup, dup2, etc.

extern volatile sig_atomic_t	g_signal_status;

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
	char		**envp;
	t_history	*history;
	t_token		*lst;
	int			status;
	int			exit_status;
	int			in;
	int			out;
	int			flag;
	int			env_allocated;
}				t_mini;

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

typedef struct s_tok
{
	int		i;
	int		j;
	int		len;
	int		malloc_flag;
	char	*k;
}	t_tok;

/* ************************************************************************** */
/*                                SIGNALS                                     */
/* ************************************************************************** */
void	ft_signal_setup(void);

/* ************************************************************************** */
/*                              create_token                                  */
/* ************************************************************************** */
int		input_to_tokens(char *input, t_mini *mini);
int		token(char *s, t_mini *mini);
char	*env_var_expansion(char *str, t_mini *mini);

/* ************************************************************************** */
/*                           env var expansion                               */
/* ************************************************************************** */
char	*search_env(char *search, int len, t_mini *mini);
char	*handle_env_var(char *str, int *i, t_mini *mini, char **copy);
int		quotes2(char *s, int *i, t_mini *mini);
char	*process_env_vars(char *str, t_mini *mini, char *copy);
char	*get_env(char *str, int *i, t_mini *mini);

/* ************************************************************************** */
/*                           create token utils                               */
/* ************************************************************************** */
int		handle_redirect_out(char *s, int *i, t_mini *mini);
int		handle_redirect_in(char *s, int *i, t_mini *mini);
int		handle_pipe(char *s, int *i, t_mini *mini);
int		check_sep(char *s, int *i, t_mini *mini);
int		process_char(char *s, t_tok *tok, t_mini *mini);
int		process_delimiter(char *k, int *j, char *s, t_mini *mini);
int		handle_remaining_token(t_tok *tok, t_mini *mini);
int		quotes(char *s, int *i, t_mini *mini);
bool	is_delimiter(char ch);
bool	is_quotes(char ch);
void	skip_spaces(char *s, int *i);
char	*add_copy_size(char *copy, size_t new_total_size);
char	*create_token(char c, char *k, int double_char);
char	*allocate_token(int len);
int		handle_token_start(char *s, t_tok *tok, t_mini *mini);
//int		handle_empty_quotes(char *s, int *i);
int		handle_empty_quotes(char *s, int *i, t_mini *mini);
int		len_next(char *str, int i, t_mini mini);
int		handle_token2(t_tok *tok, t_mini *mini);

/* ************************************************************************** */
/*                          token list utils                                  */
/* ************************************************************************** */
int		add_to_list(char *k, t_mini *mini);
void	ft_t_lstadd_back(t_token **lst, t_token *new);
void	print_list(t_mini *mini);
t_token	*ft_t_lstnew(char *content);
void	add_empty(t_mini *mini);

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
/*                             SET TYPES                                      */
/* ************************************************************************** */
int		count_pipes(t_token *lst);
int		set_types(t_token *lst);
int		reg(char *str);
int		check_errors(t_token *lst);

/* ************************************************************************** */
/*                             DISTRIBUTE                                     */
/* ************************************************************************** */
char	**build_exe(t_token *lst);
char	*find_path(char *argv, char *env[]);
char	*get_path(char **argv, char **envp, t_mini *mini);
char	*get_path2(char *argv, char **envp);
int		builtin(char **arg, t_mini *mini);
int		create_pipe(int pipe_fd[2]);
int		dis_b(t_mini *mini);
int		distribute(t_mini *mini, t_token *current);
int		exe(char **arg, t_mini *mini);
int		execute_builtin_with_redirection(char **arg, t_mini *mini, int fd[2]);
int		execute_external_command(char **arg, t_mini *mini, int fd[2]);
int		execute_external_command2(char **arg, t_mini *mini, int fd[2]);
int		is_builtin(char *arg);
int		is_env(char *env[]);
int		number_of_arguments(t_token *lst);
int		validate_command_path(char **arg, t_mini *mini, char **path);
void	execute_command(char **arg, t_mini *mini);
void	print_array(char **arg);
void	reset_dup2(t_mini *mini);
int		setup_pipe(int fd[2], int flag);
void	handle_parent_process(int fd[2], int flag, pid_t pid, t_mini *mini);

/* ************************************************************************** */
/*                             FILE HANDLING                                  */
/* ************************************************************************** */
int		file_in(t_token *lst);
int		file_out(t_token *lst);
int		input_file(int type, char *file_name);
int		output_file(int type, char *file_name);
void	here_doc(char *limiter);

/* ************************************************************************** */
/*                              EXECUTE BUILTINS                              */
/* ************************************************************************** */
int		ft_cd(char **arg);
int		ft_echo(char **arg, t_mini *mini);
int		ft_env(char **envp);
void	ft_exit(char **command, t_mini *mini);
int		ft_export(char **command, t_mini *mini);
int		ft_pwd(void);
int		ft_unset(char **arg, t_mini *mini);
void	is_block(char *arg);

/* ************************************************************************** */
/*                             BUILTIN UTILS                                  */
/* ************************************************************************** */
char	**copy_str_array(char **orig, char **copy);
char	**sort_array(char **to_sort, int iterations);
char	*get_current_directory(void);
char	*mod_cwd(char *cwd, char *path);
char	*rm_last_dir(char *cwd);
int		count_env_variables(char **envp);
int		export_no_arg(char **envp);
int		export_with_arg(char **command, t_mini *mini);
int		find_env_index(char *name, t_mini *mini);
int		find_env_var(char **envp, char *var);
int		handle_new_env_variable(char *name, t_mini *mini);
int		is_valid_identifier(char *str);
int		parse_export_arg(char **command, int i, char **name, char **value);
int		validate_name(char **command, int *i);
void	print_env(char *env);

/* ************************************************************************** */
/*                                FREE                                      */
/* ************************************************************************** */
void	free_mini(t_mini *mini);
void	free_str_array(char **to_free);
void	clear_t_history(t_mini *mini);
void	free_list(t_token *lst);
void	reset_input(char *input, t_mini *mini);

/* ************************************************************************** */
/*                             CLOSE PROGRAM                                  */
/* ************************************************************************** */
void	ft_close(int exit_status, char *input, char **arg, t_mini *mini);

#endif
