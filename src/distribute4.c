/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:10:53 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/30 21:33:18 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("%d\n", errno);
		exit(errno);
	}
	return (0);
}

int	setup_pipe(int fd[2], int flag)
{
	if (flag && !create_pipe(fd))
		return (0);
	return (1);
}

void	handle_parent_process(int fd[2], int flag, pid_t pid, t_mini *mini)
{
	int	status;

	if (flag)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		mini->exit_status = WEXITSTATUS(status);
}
