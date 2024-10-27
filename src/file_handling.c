/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:36:16 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 12:44:15 by eedwards         ###   ########.fr       */
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

int input_file(int type, char *file_name)
{
	int fileout;

	if (type == INPUT)
	{
		fileout = open(file_name, O_RDONLY, 0777);
		if (fileout == -1)
		{
			ft_putstr_fd("Error opening input file\n", 2);
			ft_putstr_fd(file_name, 2);
			return (-1);
		}
	}
	else if (type == HEREDOC)
	{
		//fileout = handle_heredoc(file_name);
		if (fileout == -1)
		{
			ft_putstr_fd("Error handling heredoc\n", 2);
			ft_putstr_fd(file_name, 2);
			return (-1);
		}
	}
	else
	{
		ft_putstr_fd("Invalid file type\n", 2);
		return (-1);
	}
	return (fileout);
}

int output_file(int type, char *file_name)
{
	int fileout;

	if (type == OUTPUT)
	{
		fileout = open(file_name, O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (fileout == -1)
		{
			ft_putstr_fd("Error opening output file\n", 2);
			ft_putstr_fd(file_name, 2);
			return (1);
		}
	}
	if (type == APPEND)
	{
		fileout = open(file_name, O_APPEND | O_CREAT | O_RDWR, 0000644);
		if (fileout == -1)
		{
			ft_putstr_fd("Error opening append file\n", 2);
			ft_putstr_fd(file_name, 2);
			return (1);
		}
	}
	return (fileout);
}
