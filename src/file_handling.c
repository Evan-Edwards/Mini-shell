/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:36:16 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 18:00:24 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handles child process for heredoc
// Reads input until delimiter is found or EOF
// Writes input to pipe and exits
static void	handle_heredoc_child(int *fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		if (write(fd[1], line, ft_strlen(line)) == -1)
			ft_putstr_fd("Write error", 2);
		free(line);
	}
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

// Creates heredoc functionality using pipe and fork
// Parent process waits for child and redirects input
// Returns void, prints error messages on failure
void	here_doc(char *limiter)
{
	pid_t	reader;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Pipe error", 2);
		return ;
	}
	reader = fork();
	if (reader == -1)
	{
		ft_putstr_fd("Fork error", 2);
		return ;
	}
	if (reader == 0)
		handle_heredoc_child(fd, limiter);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	wait(NULL);
}

// Handles input file redirection for heredoc and input files
// Returns -1 on error, 1 on success, and processes heredoc separately
static int	process_input_files(t_token *lst, int *file_fd)
{
	while (lst && lst->type != PIPE)
	{
		if ((lst->type == 4 || lst->type == 5) && lst->next)
		{
			*file_fd = input_file(lst->type, lst->next->content);
			if (*file_fd < 0)
				return (-1);
			if (lst->type == HEREDOC)
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

// Main file input handler that processes redirections
// Returns -1 on error, 1 on success
int	file_in(t_token *lst)
{
	int	file_fd;
	int	result;

	file_fd = -1;
	result = process_input_files(lst, &file_fd);
	if (result != 0)
		return (result);
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
