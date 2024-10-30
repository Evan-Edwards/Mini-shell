/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:04:57 by ttero             #+#    #+#             */
/*   Updated: 2024/10/30 12:46:55 by eedwards         ###   ########.fr       */
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

/* int	validate_command_path(char **arg, t_mini *mini, char **path)
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
 */

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


// Executes an external command with proper path resolution
// Handles pipe redirection and error reporting
int	execute_external_command2(char **arg, t_mini *mini, int fd[2])
{
	int		exec_result;
	char	*path;

	if (!validate_command_path(arg, mini, &path))
		ft_close(EXIT_FAILURE, NULL, arg, mini);
	if (mini->flag == 1)
		dup2(fd[1], STDOUT_FILENO);
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
	exit(EXIT_SUCCESS);
}

int	setup_pipe(int fd[2], int flag)
{
	if (flag && !create_pipe(fd))
		return (0);
	return (1);
}

void	handle_parent_process(int fd[2], int flag, pid_t pid, t_mini *mini)
{
    char buffer[4096];
    ssize_t bytes_read;

	if (flag) {
		close(fd[1]);  // Close write end in the parent
		while ((bytes_read = read(fd[0], buffer, sizeof(buffer))) > 0) {
			// Optionally write to STDOUT or discard if not needed
			write(STDOUT_FILENO, buffer, bytes_read);
		}
		close(fd[0]);
	}
	waitpid(pid, &(mini->exit_status), 0);
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
	is_block(arg[0]);
	execute_command(arg, mini);
	free_str_array(arg);
	return (1);
}
