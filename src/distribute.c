/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:04:57 by ttero             #+#    #+#             */
/*   Updated: 2024/10/29 13:28:34 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	**build_exe(t_token *lst)
{
	int		arg_num;
	char	**arg_array;
	int		i;

	i = 0;
	arg_num = number_of_arguments(lst);
	if (arg_num == 0)
	{
		return (NULL);
	}
	arg_array = malloc(sizeof(char*) * (arg_num +1));
	while (lst->next != NULL && lst->type != PIPE)
	{
		if (lst->type >= 3)
		{
			lst->next->type = 6;
			lst = lst->next;
		}
		else
		{
			arg_array[i] = lst->content;
			i++;
		}
		if (lst->next != NULL)
			lst = lst->next;
	}
	if (lst->type <= 2)
	{
		arg_array[i] = lst->content;
		i++;
	}
	//arg_array[i] = malloc(1);
	arg_array[i] = 0;
	return (arg_array);
}*/

/* //Processes a token list to build an array of arguments
//Handles redirection tokens (type >= 3) by marking following tokens
//Collects command and argument tokens (type <= 2) into the array
static void	process_token(t_token *lst, char **arg_array, int *i)
{
	while (lst->next != NULL && lst->type != PIPE)
	{
		if (lst->type >= 3)
		{
			lst->next->type = 8;
			lst = lst->next;
		}
		else
		{
			arg_array[*i] = lst->content;
			(*i)++;
		}
		if (lst->next != NULL)
			lst = lst->next;
	}
	if (lst->type <= 2)
	{
		arg_array[*i] = lst->content;
		(*i)++;
	}
} */


//Processes a single token and updates the argument array
//Returns: -1 on allocation error, 0 for redirection tokens, 1 for normal tokens
//Updates: arg_array with new argument, i with new array position
static int handle_token(t_token *lst, char **arg_array, int *i)
{
    if (lst->type >= 3)
    {
        lst->next->type = 8;
        return (0);
    }
    arg_array[*i] = ft_strdup(lst->content);
    if (!arg_array[*i])
        return (-1);
    (*i)++;
    return (1);
}

//Processes tokens to build array of command arguments
//Returns: -1 on allocation error, otherwise number of arguments processed
//Handles: Command tokens, arguments, and marks redirection targets
//Updates: arg_array with arguments, NULL terminated
static int process_token_args(t_token *lst, char **arg_array)
{
	int i;
	int result;

	i = 0;
	while (lst->next != NULL && lst->type != PIPE)
	{
		result = handle_token(lst, arg_array, &i);
		if (result == -1)
			return (-1);
		if (result == 0)
			lst = lst->next;
		if (lst->next != NULL)
			lst = lst->next;
	}
	if (lst->type <= 2)
	{
		arg_array[i] = ft_strdup(lst->content);
		if (!arg_array[i])
			return (-1);
		i++;
	}
	arg_array[i] = NULL;
	return (i);
}

//Builds an executable command array from a token list
//Returns NULL if no arguments are found or on allocation failure
//Allocates memory for the array and terminates it with NULL
//Caller must free the returned array using free_str_array
char **build_exe(t_token *lst)
{
    int     arg_num;
    char    **arg_array;
    int     result;

    arg_num = number_of_arguments(lst);
    if (arg_num == 0)
        return (NULL);
    arg_array = malloc(sizeof(char *) * (arg_num + 1));
    if (!arg_array)
        return (NULL);
    result = process_token_args(lst, arg_array);
    if (result == -1)
    {
        free_str_array(arg_array);
        return (NULL);
    }
    return (arg_array);
}

int execute_builtin_with_redirection(char **arg, t_mini *mini, int fd[2])
{
	int original_stdout;
	int status;

	original_stdout = dup(STDOUT_FILENO);
	if (mini->flag == 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	status = builtin(arg, mini);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	if (status != 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(" command failed\n", 2);
		ft_close(EXIT_FAILURE, NULL, arg, mini);
	}
	return status;
}

int execute_external_command(char **arg, t_mini *mini, int fd[2])
{
	int exec_result;
	char *path;

	close(fd[0]);
	if (!validate_command_path(arg, mini, &path))
		return (1);
	if (mini->flag == 1) // Redirect output if in pipeline
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);

	exec_result = execve(path, arg, mini->envp);
	if (exec_result == -1)
	{
		ft_printf_error("%s: %s\n", path, strerror(errno));
		exit(errno);
	}
	return (0);
}

// Executes a command, either built-in or external
// Manages piping for both types of commands
void execute_command(char **arg, t_mini *mini)
{
	int fd[2];
	pid_t pid ;
	int is_builtin_cmd;

	is_builtin_cmd = is_builtin(arg[0]);
	if (is_builtin_cmd && mini->flag == 0)
		mini->exit_status = builtin(arg, mini);
	else
	{
		if (mini->flag == 1 && !create_pipe(fd))
			return;
		pid = fork();
		if (pid == -1)
		{
			ft_printf_error("Fork error\n");
			return;
		}
		else if (pid == 0)
		{
			if (is_builtin_cmd)
				execute_builtin_with_redirection(arg, mini, fd);
			else
				execute_external_command(arg, mini, fd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			waitpid(pid, &(mini->exit_status), 0);
		}
	}
}

//Handles input and output redirection using file_in and file_out
//Builds an argument array using build_exe
//Checks if the command is a built-in using is_builtin
//Executes the command (either built-in or external)
//Returns 0 on error, 1 on success
int	distribute(t_mini *mini, t_token *current)
{
	char	**arg;
	int		file_fd;

	file_fd = -1;
	if (file_in(current) < 0)
	{
		mini->exit_status = 1;
		return (0);
	}
	file_fd = file_out(current);
	if (file_fd < 0)
	{
		mini->exit_status = 1;
		return (0);
	}
	arg = build_exe(current);
	if (arg == NULL)
		return (0);
	execute_command(arg, mini);
	/* if (mini->exit_status != 0)
		mini->loop = 0; */
	free_str_array(arg);
	return (1);
}

void	reset_dup2(t_mini *mini)
{
	dup2(mini->in, STDIN_FILENO);
	dup2(mini->out, STDOUT_FILENO);
}


//Distributes commands across pipes
//Processes multiple commands separated by pipes
//Sets flags for pipe handling and manages command flow
 int	dis_b(t_mini *mini)
{
	t_token	*current;
	int		pipe_num;
	int		i;

	current = mini->lst;
	mini->flag = 0;
	pipe_num = count_pipes(mini->lst);
	i = 0;
	if (pipe_num > 0)
		mini->flag = 1;
	// Execute first command
	distribute(mini, current);
	while (current != NULL)
	{
		if (current->type == PIPE)
		{
			if (i == pipe_num - 1)  // Last pipe
				mini->flag = 0;
			distribute(mini, current->next);
			i++;
		}
		current = current->next;
	}
	reset_dup2(mini);
	return (1);
}

