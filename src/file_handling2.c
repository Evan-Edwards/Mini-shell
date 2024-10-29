/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:00:38 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 18:00:51 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (1);
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
