/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:04:57 by ttero             #+#    #+#             */
/*   Updated: 2024/10/30 21:38:48 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Executes a builtin command with output redirection if needed
// Returns the status of the builtin execution
int	execute_builtin_with_redirection(char **arg, t_mini *mini, int fd[2])
{
	int	original_stdout;
	int	status;

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
	return (status);
}

// Executes an external command with proper path resolution
// Handles pipe redirection and error reporting
int	execute_external_command(char **arg, t_mini *mini, int fd[2])
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
		exit(errno);
	}
	return (0);
}

// Handles the child process execution for both builtin and external commands
// Exits the process after command execution
static void	handle_child_process(char **arg, t_mini *mini, int fd[2],
	int is_builtin)
{
	if (is_builtin)
		execute_builtin_with_redirection(arg, mini, fd);
	else if (mini->flag == 1)
		execute_external_command(arg, mini, fd);
	else
		execute_external_command2(arg, mini, fd);
	ft_close(EXIT_SUCCESS, NULL, arg, mini);
}

// Main execution function that handles builtin and external commands
// Sets up pipes if needed and manages child process creation
void	execute_command(char **arg, t_mini *mini)
{
	int		fd[2];
	pid_t	pid;
	int		is_builtin_cmd;

	is_builtin_cmd = is_builtin(arg[0]);
	if (is_builtin_cmd && mini->flag == 0)
	{
		mini->exit_status = builtin(arg, mini);
		return ;
	}
	if (!setup_pipe(fd, mini->flag))
		return ;
	pid = fork();
	if (pid == -1)
	{
		ft_printf_error("Fork error\n");
		return ;
	}
	if (pid == 0)
		handle_child_process(arg, mini, fd, is_builtin_cmd);
	handle_parent_process(fd, mini->flag, pid, mini);
}

// Distributes command execution with proper file redirection handling
// Returns 1 on success, 0 on failure
int	distribute(t_mini *mini, t_token *current)
{
	char	**arg;
	int		file_fd;

	g_signal_status = 2;
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
	free_str_array(arg);
	return (1);
}
