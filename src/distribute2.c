/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:03:11 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 12:03:56 by eedwards         ###   ########.fr       */
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

void	print_array(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("%s\n", arg[i]);
		i++;
	}
	printf("%s\n", arg[i]);
}

//counts number of arguments in a linked list of tokens up to end or pipe
//skips tokens of type 3 ?
int	number_of_arguments(t_token *lst)
{
	int	i;

	i = 0;
	while (lst && lst->type != PIPE)
	{
		if (lst->type < 3)
			i++;
		else if (lst->type >= 3 && lst->next)
		{
			lst->next->type = 3;
			lst = lst->next;
		}
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
	return (i);
}
