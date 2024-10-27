/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:35:34 by ttero             #+#    #+#             */
/*   Updated: 2024/10/27 22:19:18 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("Pipe error\n", 2);
		return(0);
	}
	return (1);
}

 int exe(char **arg,t_mini *mini)
{
	char *path;
	pid_t pid1;
	int status;

	(void)mini;  //for make
	path = (NULL); //for make
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


