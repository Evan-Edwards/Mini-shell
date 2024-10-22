/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:17:17 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/22 11:34:10 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_current_directory(void)
{
	char	*cwd;

	cwd = getcwd
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = get_current_directory();
	if (cwd == NULL)
		return (0);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (1);
}



//store cwd in data struct?