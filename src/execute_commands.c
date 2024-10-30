/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:35:34 by ttero             #+#    #+#             */
/*   Updated: 2024/10/30 12:08:04 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Creates a pipe and handles pipe errors
//Returns 1 on success, 0 on failure
//Sets up pipe_fd array with read and write ends
int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("Pipe error\n", 2);
		return (0);
	}
	return (1);
}

//Validates and retrieves the command path
//Returns 1 on success, 0 if path not found
//Sets path pointer to resolved command path
int	validate_command_path(char **arg, t_mini *mini, char **path)
{
	if (mini->flag == 0)
		*path = get_path(arg, mini->envp, mini);
	else
		*path = get_path2(arg[0], mini->envp);
	if (*path == NULL)
	{
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		mini->exit_status = 127;
		if (mini->flag == 0)
			ft_close(127, NULL, arg, mini);
		else
			ft_close(EXIT_FAILURE, NULL, arg, mini);
	}
	return (1);
}

//Executes the command in child process using execve
//Handles execution errors and exits with appropriate status
//Returns 0 on success (though never reaches this due to execve)
static int	execute_child_process(char **arg, t_mini *mini, int fd[2])
{
	int		exec_result;
	char	*path;

	close(fd[0]);
	if (!validate_command_path(arg, mini, &path))
		return (1);
	if (mini->flag == 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_result = execve(path, arg, mini->envp);
	if (exec_result == -1)
	{
		ft_printf_error("%s: %s\n", path, strerror(errno));
		if (mini->flag == 0)
			exit(errno);
		else
			exit (1);
	}
	return (0);
}

//Manages command execution process for external commands
//Handles path validation, process creation, and status collection
//Returns command exit status or error code
int	exe(char **arg, t_mini *mini)
{
	pid_t	pid1;
	int		status;
	int		fd[2];

	status = 0;
	create_pipe(fd);
	pid1 = fork();
	if (pid1 == -1)
	{
		ft_putstr_fd("Fork error", 2);
		return (1);
	}
	if (pid1 == 0)
		execute_child_process(arg, mini, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid1, &status, 0);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}
