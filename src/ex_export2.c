/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:43:14 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 15:47:48 by eedwards         ###   ########.fr       */
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

// Extracts variable name and value from export command
// Allocates new strings for extracted parts
// Returns 0 on success, 1 on failure
int	parse_export_arg(char **command, int i, char **name, char **value)
{
	*name = ft_substr(command[1], 0, i);
	if (*name == NULL)
		return (1);
	*value = NULL;
	if (command[1][i] == '=')
		*value = ft_substr(command[1], i + 1, ft_strlen(command[1]) - i - 1);
	return (0);
}

// Adds new environment variable to mini->envp
// Allocates new array and copies existing variables
// Returns 0 on success, 1 on failure
int	handle_new_env_variable(char *name, t_mini *mini)
{
	char	**new_env;
	int		env_count;

	env_count = count_env_variables(mini->envp);
	new_env = malloc((env_count + 2) * sizeof(char *));
	if (new_env == NULL)
		return (1);
	new_env = copy_str_array(mini->envp, new_env);
	if (new_env == NULL)
	{
		free_str_array(new_env);
		return (1);
	}
	new_env[env_count] = ft_strjoin(name, "=");
	if (new_env[env_count] == NULL)
	{
		free_str_array(new_env);
		return (1);
	}
	new_env[env_count + 1] = NULL;
	if (mini->env_allocated)
		free_str_array(mini->envp);
	mini->envp = new_env;
	mini->env_allocated = 1;
	return (0);
}
