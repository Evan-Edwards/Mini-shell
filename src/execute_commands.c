/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:35:34 by ttero             #+#    #+#             */
/*   Updated: 2024/10/27 11:39:03 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int input_file(int type, char *file_name)
{
	int fileout;

	if (type == INPUT)
	{
		fileout = open(file_name, O_RDONLY, 0777);
		if (fileout == -1)
		{
			printf("%s: %s\n", file_name, strerror(errno));
			return (-1);
		}
	}
	if (type == HEREDOC)
	{
		//fileout = handle_heredoc(file_name);
		if (fileout == -1)
		{
			printf("%s: %s\n", file_name, strerror(errno));
			return (-1);
		}
	}
	return (fileout);
}

int output_file (int type, char *file_name)
{
	int fileout;

	if (type == OUTPUT)
	{
		fileout = open(file_name, O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (fileout == -1)
		{
			printf("%s: %s\n", file_name, strerror(errno));
			return (1);
		}
	}
	if (type == APPEND)
	{
		fileout = open(file_name, O_APPEND | O_CREAT | O_RDWR, 0000644);
		if (fileout == -1)
		{
			printf("%s: %s\n", file_name, strerror(errno));
			return (1);
		}
	}
	return (fileout);
}


int create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("Pipe error\n", 2);
		return(0);
	}
	return (1);
}


int exe(char **arg,t_mini *mini, char **envp)
{
	char *path;
	pid_t pid1;
	int status;

	(void)mini;  //for make
	path = (NULL); //for make
	//path = get_path2(arg[0], envp); //commented so make works
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
		if (execve(path, arg, envp) == -1)
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
