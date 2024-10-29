/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:43:08 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 18:42:37 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Copies strings from old array to new, skipping specified index
// Returns new array or NULL on failure
static char	**copy_array_except_index(char **arr, char **new_arr, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i])
	{
		if (i != index)
		{
			new_arr[j] = ft_strdup(arr[i]);
			if (!new_arr[j])
			{
				free_str_array(new_arr);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	new_arr[j] = NULL;
	return (new_arr);
}

// Removes string at index from array and returns new array
// Returns NULL on failure
static char	**remove_str_from_array(char **arr, int index)
{
	char	**new_arr;
	int		size;

	size = 0;
	while (arr[size])
		size++;
	new_arr = malloc(sizeof(char *) * size);
	if (!new_arr)
		return (NULL);
	return (copy_array_except_index(arr, new_arr, index));
}

// Processes single unset argument
// Returns 0 on success, 1 on failure
static int	process_unset_arg(char *arg, t_mini *mini)
{
	int		env_index;
	char	**new_envp;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("unset: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	env_index = find_env_var(mini->envp, arg);
	if (env_index != -1)
	{
		new_envp = remove_str_from_array(mini->envp, env_index);
		if (new_envp)
		{
			if (mini->env_allocated)
				free_str_array(mini->envp);
			mini->envp = new_envp;
			mini->env_allocated = 1;
		}
	}
	return (0);
}

// Main unset command handler
// Returns 0 on success, 1 if any argument is invalid
int	ft_unset(char **arg, t_mini *mini)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (arg[i])
	{
		if (process_unset_arg(arg[i], mini))
			status = 1;
		i++;
	}
	return (status);
}
