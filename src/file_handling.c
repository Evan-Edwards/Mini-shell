/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:36:16 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 22:10:54 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void here_doc(char *limiter)
{
	pid_t reader;
	int fd[2];
	char *line;

	if (pipe(fd) == -1)
	{
		ft_printf_error("Pipe error");
		return;
	}
	reader = fork();
	if (reader == -1)
	{
		ft_printf_error("Fork error");
		return;
	}
	if (reader == 0)
	{
		close(fd[0]);
		while ((line = get_next_line(STDIN_FILENO)) != NULL)
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
	}
}

//Handles input redirection (<)
//Processes input file tokens until pipe or end of list
//Returns -1 on error, 1 on success
//Sets up file descriptor for input and handles dup2
int	file_in(t_token *lst)
{
	int	file_fd;

	file_fd = -1;
	while (lst && lst->type != PIPE)
	{
		if ((lst->type == 4 || lst->type == 5) && lst->next)
		{
			file_fd = input_file(lst->type, lst->next->content);
			if (file_fd < 0)
				return (-1);
			else if (lst->type == HEREDOC)
				return 1;
		}
		lst = lst->next;
	}
	if (file_fd != -1)
	{
		if (dup2(file_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(file_fd);
			return (-1);
		}
		close(file_fd);
	}
	return (1);
}

//Handles output redirection (> and >>)
//Processes output file tokens until pipe or end of list
//Returns -1 on error, 1 on success
//Sets up file descriptor for output and handles dup2
int	file_out(t_token *lst)
{
	int	file_fd;

	file_fd = -1;
	while (lst->next != NULL && lst->type != PIPE)
	{
		if (lst->type >= 6)
		{
			file_fd = output_file(lst->type, lst->next->content);
			if (file_fd < 0)
				return (-1);
		}
		lst = lst->next;
	}
	if (file_fd != -1)
	{
		if (dup2(file_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(file_fd);
			return (-1);
		}
		close(file_fd);
	}
	return (1);
}

//Utility function to print file-related error messages to stderr
//Prints error message followed by filename
static void	print_file_error(const char *error_msg, char *file_name)
{
	ft_putstr_fd((char *)error_msg, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(file_name, 2);
}

//Opens and sets up input files for redirection
//Handles both regular input files (<) and heredocs (<<)
//Returns file descriptor or -1 on error
//Prints appropriate error message on failure
int	input_file(int type, char *file_name)
{
	int			fileout;
	const char	*error_msg;

	fileout = -1;
	error_msg = "Error: invalid file type";
	if (type == INPUT)
	{
		fileout = open(file_name, O_RDONLY);
		if (fileout == -1)
		{
			ft_printf_error("%s: %s\n", file_name, strerror(errno));
			return (-1);
		}
	}
	else if (type == 5)
	{
		here_doc(file_name);
		return 1;
	}
	if (fileout == -1)
		print_file_error(error_msg, file_name);
	return (fileout);
}

//Opens and sets up output files for redirection
//Handles both regular output (>) and append (>>) modes
//Returns file descriptor or -1 on error
//Creates file if it doesn't exist with permissions 0644
int	output_file(int type, char *file_name)
{
	int			fileout;
	const char	*error_msg;
	int			flags;

	fileout = -1;
	error_msg = "Error: invalid file type";
	flags = O_CREAT | O_RDWR;
	if (type == OUTPUT)
	{
		flags |= O_TRUNC;
		error_msg = "Error opening output file";
	}
	if (type == APPEND)
	{
		flags |= O_APPEND;
		error_msg = "Error opening append file";
	}
	if (type == OUTPUT || type == APPEND)
		fileout = open(file_name, flags, 0644);
	if (fileout == -1)
		print_file_error(error_msg, file_name);
	return (fileout);
}
