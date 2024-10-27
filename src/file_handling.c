/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:36:16 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 13:06:16 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handles input redirection
int	file_in(t_token *lst)
{
	int	file_fd;

	file_fd = -1;
	while (lst && lst->type != PIPE)
	{
		if (lst->type == 4 && lst->next)
		{
			file_fd = input_file(lst->type, lst->next->content);
			if (file_fd < 0)
				return (-1);
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

//handles output redirection
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

static void	print_file_error(const char *error_msg, const char *file_name)
{
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(file_name, 2);
}

int	input_file(int type, char *file_name)
{
	int			fileout;
	const char	*error_msg;

	fileout = -1;
	error_msg = "Error: invalid file type";
	if (type == INPUT)
	{
		fileout = open(file_name, O_RDONLY);
		error_msg = "Error opening input file";
	}
	else if (type == HEREDOC)
	{
		//fileout = handle_heredoc(file_name);
		error_msg = "Error handling heredoc";
	}
	if (fileout == -1)
		print_file_error(error_msg, file_name);
	return (fileout);
}

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

