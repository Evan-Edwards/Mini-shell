/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_export_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:00:24 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 17:13:42 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Finds the index of an environment variable by name
// Returns the index if found, -1 otherwise
int	find_env_index(char *name, t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->envp[i])
	{
		if (ft_strncmp(mini->envp[i], name, ft_strlen(name)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

// Validates the name of an environment variable
// Returns 1 if valid, 0 otherwise
// Updates the index i to the position of '=' if present
int	validate_name(char **command, int *i)
{
	if (command == NULL || command[0] == NULL || command[1] == NULL)
		return (0);
	while (command[1][*i] && command[1][*i] != '=')
	{
		if (command[1][*i] != '_' && !ft_isalnum(command[1][*i]))
			return (0);
		(*i)++;
	}
	return (i);
}

// Adds a new environment variable to mini->envp
// Returns 1 on success, 0 on failure
static int	handle_new_env_variable(char *name, char *value, t_mini *mini)
{
	char	**new_env;
	int		env_count;

	env_count = count_env_variables(mini->envp);
	new_env = malloc((env_count + 2) * sizeof(char *));
	if (new_env == NULL)
		return (0);
	new_env = copy_str_array(mini->envp, new_env);
	if (new_env == NULL)
	{
		free_str_array(new_env);
		return (0);
	}
	new_env[env_count] = ft_strjoin(name, "=");
	if (new_env[env_count] == NULL)
	{
		free_str_array(new_env);
		return (0);
	}
	new_env[env_count + 1] = NULL;
	mini->envp = new_env;
	return (1);
}

// Updates an existing environment variable in mini->envp
// Returns 1 on success, 0 on failure
static int	update_existing_env_variable(char *name, char *value, int index,
	t_mini *mini)
{
	char	*temp;

	free(mini->envp[index]);
	if (value == NULL)
	{
		mini->envp[index] = ft_strdup(name);
		return (mini->envp[index] != NULL);
	}
	temp = ft_strjoin(name, "=");
	if (temp == NULL)
		return (0);
	mini->envp[index] = ft_strjoin(temp, value);
	free(temp);
	return (mini->envp[index] != NULL);
}

// Handles the export command with arguments
// Adds a new environment variable or updates an existing one
// Returns 1 on success, 0 on failure
int	export_with_arg(char **command, t_mini *mini)
{
	char	*name;
	char	*value;
	int		i;
	int		result;

	i = 0;
	if (!validate_name(command, &i))
		return (0);
	name = ft_substr(command[1], 0, i);
	if (name == NULL)
		return (0);
	value = NULL;
	if (command[1][i] == '=')
		value = ft_substr(command[1], i + 1, ft_strlen(command[1]) - i - 1);
	i = find_env_index(name, mini);
	if (i == -1)
		result = handle_new_env_variable(name, value, mini);
	else
		result = update_existing_env_variable(name, value, i, mini);
	free(name);
	free(value);
	return (result);
}