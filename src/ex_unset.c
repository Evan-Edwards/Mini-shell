/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:08:25 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/24 13:51:58 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns 1 if arg starts with a letter or underscore and then only contains
//letters, numbers, or underscores
//otherwise returns 0
int	check_arg_valid(char *env)
{
	int	i;

	i = 0;
	if (ft_isalpha(env[i]) == 0 && env[i] != '_')
		return (0);
	while (env[i])
	{
		if (ft_isalnum(env[i]) == 0 && env[i] != '_')
			return (0);
	}
	return (1);
}

void	remove_str_from_array(char ***envp, int *j)
{
	int	i;

	free((*envp)[*j]);
	i = *j;
	while (*envp[i])
	{
		(*envp)[i] = (*envp)[i + 1];
		i++;
	}
}

//returns 1 for success, 0 for failure
int	ft_unset(char **envp, char **to_unset)
{
	int	i;
	int	j;

	i = 0;
	if (!envp || !to_unset)
		return (0);
	while (to_unset[i])
	{
		if (check_arg_valid(to_unset[i] == 0))
		{
			ft_putstr_fd("arguments for unset not valid", 2);
			return (0);
		}
		j = 0;
		while (envp[j])
		{
			if (ft_strncmp(to_unset[i], envp[j], ft_strlen(to_unset[i]) == 0
				&& envp[j][ft_strlen(to_unset[i]) + 1] == '='))
				remove_str_from_array(&envp, &j);
		}
		i++;
	}


	return (1);
}