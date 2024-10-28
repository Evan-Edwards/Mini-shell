/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:35:34 by ttero             #+#    #+#             */
/*   Updated: 2024/10/28 06:22:47 by eedwards         ###   ########.fr       */
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
static int	validate_command_path(char **arg, char **envp, char **path)
{
	*path = get_path2(arg[0], envp);
	if (*path == NULL)
	{
		ft_printf("%s: command not found:\n", arg[0]);
		return (0);
	}
	return (1);
}

//Executes the command in child process using execve
//Handles execution errors and exits with appropriate status
//Returns 0 on success (though never reaches this due to execve)
static int	execute_child_process(char *path, char **arg, char **envp)
{
	int	exec_result;

	exec_result = execve(path, arg, envp);
	if (exec_result == -1)
	{
		ft_printf("%s: %s\n", path, strerror(errno));
		exit(errno);
	}
	return (0);
}

//Manages command execution process for external commands
//Handles path validation, process creation, and status collection
//Returns command exit status or error code
int	exe(char **arg, t_mini *mini)
{
	char	*path;
	pid_t	pid1;
	int		status;

	if (!validate_command_path(arg, mini->envp, &path))
		return (1);
	pid1 = fork();
	if (pid1 == -1)
	{
		ft_printf("Fork error");
		free(path);
		return (1);
	}
	if (pid1 == 0)
		execute_child_process(path, arg, mini->envp);
	waitpid(pid1, &status, 0);
	free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}

/*int	exe(char **arg, t_mini *mini)
{
	char	*path;
	pid_t	pid1;

	int		status;

	path = get_path2(arg[0], mini->envp); //commented so make works
	if (path == NULL)
	{
		ft_printf("%s: command not found:\n", arg[0]);
		return (1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		ft_printf("Fork error");
		return (1);
	}
	if (pid1 == 0)
	{
		if (execve(path, arg, mini->envp) == -1)
		{
			ft_printf("%s: %s\n", path, strerror(errno));
			exit(errno);
		}
	}
	waitpid(pid1, &status, 0);
	free (path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}
*/
