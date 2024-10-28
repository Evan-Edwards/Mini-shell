/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:08:25 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 16:06:35 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns 1 if arg starts with a letter or underscore and then only contains
//letters, numbers, or underscores
//otherwise returns 0
static int	check_arg_valid(char *env)
{
	int	i;

	i = 0;
	if (ft_isalpha(env[i]) == 0 && env[i] != '_')
		return (0);
	while (env[i])
	{
		if (ft_isalnum(env[i]) == 0 && env[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

//removes str at position j in the envp arr
//moves the rest up 1 position and sets previous last position to NULL
void	remove_str_from_array(char ***envp, int *j)
{
	int	i;

	free((*envp)[*j]);
	i = *j;
	while ((*envp)[i])
	{
		(*envp)[i] = (*envp)[i + 1];
		i++;
	}
}

//checks that args to unset are valid
//if all args valid returns 1
//if not prints out which arg is not valid and returns 0
static int	validate_unset_args(char **to_unset)
{
	int	i;

	i = 1;
	while (to_unset[i])
	{
		if (check_arg_valid(to_unset[i]) == 0)
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(to_unset[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

//unsets (removes) args in the array to_unset from envp
//uses validate_unset_args to check that args have valid characters
//finds variables to be removed from envp and removes with remove_str_from_array
int	ft_unset(char **envp, char **to_unset)
{
	int		i;
	int		j;
	size_t	len;

	if (!envp || !to_unset || !validate_unset_args(to_unset))
		return (EXIT_FAILURE);
	i = 1;
	while (to_unset[i])
	{
		j = 0;
		while (envp[j])
		{
			len = ft_strlen(to_unset[i]);
			if (ft_strncmp(to_unset[i], envp[j], len) == 0
				&& (envp[j][len] == '=' || envp[j][len] == '\0'))
			{
				remove_str_from_array(&envp, &j);
				j--;
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
