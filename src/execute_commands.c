/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:35:34 by ttero             #+#    #+#             */
/*   Updated: 2024/10/23 20:36:10 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_file (int type, char *file_name)
{
	int fileout;

	if (type == OUTPUT)
	{
		fileout = open(file_name, O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (fileout == -1)
		{
			ft_printf_error("%s: %s\n", data.file2, strerror(errno));
			return (1);
		}
	}
	if (type == APPEND)
	{
		fileout = open(file_name, O_APPEND | O_CREAT | O_RDWR, 0000644);
		if (fileout == -1)
		{
			ft_printf_error("%s: %s\n", data.file2, strerror(errno));
			return (1);
		}
	}
	if (type == INPUT)
	{
		fileout = open(file_name, O_RDONLY, 0777);;
		if (fileout == -1)
		{
			ft_printf_error("%s: %s\n", data.file2, strerror(errno));
			return (1);
		}
	}
	if (type == HEREDOC)
	{
		fileout = handle_heredoc(file_name);
		if (fileout == -1)
		{
			ft_printf_error("%s: %s\n", data.file2, strerror(errno));
			return (1);
		}
	}
}

int exec (t_token *lst, int pipe_num)
{
	int i;

	i = 0;
	while (lst->next != NULL && lst->type != PIPE)
	{
		if (lst->type > 6)
		{
			open_file(lst->type, lst->next->str);
		}
		lst = lst->next;
	}
}
