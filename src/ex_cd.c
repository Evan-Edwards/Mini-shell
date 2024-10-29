/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:43:08 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 12:06:05 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//parses for last '/' symbol
//returns substring of cwd until last /
char	*rm_last_dir(char *cwd)
{
	int		i;
	int		last;
	char	*temp;

	i = 0;
	last = 0;
	while (cwd[i])
	{
		if (cwd[i] == '/')
			last = i;
		i++;
	}
	temp = ft_substr(cwd, 0, last);
	free(cwd);
	if (temp == NULL)
		perror("Malloc failure");
	return (temp);
}

//handles the case when no argument is provided to cd
//returns the HOME directory path or NULL if HOME is not set
static char	*handle_no_arg(void)
{
	char	*dest;

	dest = getenv("HOME");
	if (dest == NULL)
	{
		ft_putstr_fd("HOME not set\n", 2);
		return (NULL);
	}
	return (dest);
}

//processes the cd command arguments to determine the destination path
//returns the appropriate path based on the argument or NULL on error
static char	*process_cd_path(char **arg)
{
	char	*dest;
	char	*cwd;

	if (arg[1] == NULL)
		return (handle_no_arg());
	if (arg[1][0] == '/')
		return (arg[1]);
	cwd = get_current_directory();
	if (cwd == NULL)
		return (NULL);
	dest = mod_cwd(cwd, arg[1]);
	return (dest);
}

static int	handle_cd_error(char **arg, char *dest)
{
	if (dest == NULL)
		ft_putstr_fd("cd: Invalid path\n", 2);
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (arg[1] && arg[1][0] != '/' && dest)
		free(dest);
	return (1);
}

//changes the current working directory based on the given arguments
//calls process_cd_path to get the destination path
//returns 1 on success, 0 on failure
int	ft_cd(char **arg)
{
	char	*dest;
	int		arg_count;

	arg_count = 0;
	while (arg[arg_count])
		arg_count++;
	if (arg_count > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	dest = process_cd_path(arg);
	if (dest == NULL || chdir(dest) == -1)
		return (handle_cd_error(arg, dest));
	if (arg[1] && arg[1][0] != '/')
		free(dest);
	return (0);
}
