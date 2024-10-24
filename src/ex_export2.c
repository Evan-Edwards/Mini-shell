/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:43:14 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/24 12:58:01 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//count how many strings are in the string array given
int	count_env_variables(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}