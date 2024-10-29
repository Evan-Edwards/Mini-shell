/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:43:08 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 10:44:59 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	find_env_var(char **envp, char *var)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && 
			(envp[i][len] == '=' || envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static char	**remove_str_from_array(char **arr, int index)
{
	char	**new_arr;
	int		i;
	int		j;
	int		size;

	size = 0;
	while (arr[size])
		size++;
	new_arr = malloc(sizeof(char *) * size);
	if (!new_arr)
		return (NULL);
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

int	ft_unset(char **arg, t_mini *mini)
{
	int		i;
	int		env_index;
	char	**new_envp;

	i = 1;
	while (arg[i])
	{
		if (!is_valid_identifier(arg[i]))
		{
			ft_putstr_fd("unset: '", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		env_index = find_env_var(mini->envp, arg[i]);
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
		i++;
	}
	return (0);
}
