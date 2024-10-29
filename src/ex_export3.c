/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_export_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:00:24 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 15:47:59 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Finds environment variable index by name in mini->envp array
// Returns index if found, -1 if not found
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

// Validates environment variable name format
// Checks for valid characters and position of equals sign
// Returns 1 if valid, 0 if invalid
int	validate_name(char **command, int *i)
{
	if (command == NULL || command[0] == NULL || command[1] == NULL)
		return (0);
	if (ft_isdigit(command[1][0]))
		return (0);
	while (command[1][*i] && command[1][*i] != '=')
	{
		if (command[1][*i] != '_' && !ft_isalnum(command[1][*i]))
			return (0);
		(*i)++;
	}
	return (*i);
}

// Creates copy of environment array if not already allocated
// Allocates new array and copies all variables
// Returns 0 on success, 1 on failure
static int	copy_env_if_needed(t_mini *mini)
{
	char	**new_env;

	if (mini->env_allocated)
		return (0);
	new_env = malloc((count_env_variables(mini->envp) + 1) * sizeof(char *));
	if (!new_env)
		return (1);
	if (!copy_str_array(mini->envp, new_env))
	{
		free(new_env);
		return (1);
	}
	mini->envp = new_env;
	mini->env_allocated = 1;
	return (0);
}

// Updates existing environment variable at given index
// Handles cases with and without value after equals sign
// Returns 0 on success, 1 on failure
static int	update_existing_env_variable(char *name, char *value, int index,
	t_mini *mini)
{
	char	*temp;

	if (copy_env_if_needed(mini))
		return (1);
	free(mini->envp[index]);
	if (value == NULL)
	{
		mini->envp[index] = ft_strdup(name);
		if (mini->envp[index] == NULL)
			return (1);
		return (0);
	}
	temp = ft_strjoin(name, "=");
	if (temp == NULL)
		return (1);
	mini->envp[index] = ft_strjoin(temp, value);
	free(temp);
	if (mini->envp[index] == NULL)
		return (1);
	return (0);
}

// Main handler for export command with arguments
// Validates input and updates environment accordingly
// Returns 0 on success, 1 on failure
int	export_with_arg(char **command, t_mini *mini)
{
	char	*name;
	char	*value;
	int		i;
	int		result;

	i = 0;
	if (!validate_name(command, &i))
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (1);
	}
	if (parse_export_arg(command, i, &name, &value))
		return (1);
	i = find_env_index(name, mini);
	if (i == -1)
		result = handle_new_env_variable(name, mini);
	else
		result = update_existing_env_variable(name, value, i, mini);
	free(name);
	if (value)
		free(value);
	return (result);
}
