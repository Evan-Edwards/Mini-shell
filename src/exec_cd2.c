/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:44:26 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/23 16:42:09 by eedwards         ###   ########.fr       */
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