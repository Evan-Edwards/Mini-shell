/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:17:35 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 06:30:50 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//creates a copy of the the str array given using strdup
//failure: returns NULL if malloc in strdup fails or if orig or copy don't exist
char	**copy_str_array(char	**orig, char **copy)
{
	int	i;

	i = 0;
	if (!orig || !copy)
		return (NULL);
	while (orig[i])
	{
		copy[i] = ft_strdup(orig[i]);
		if (copy[i] == NULL)
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

//sorts string array given alphabetically
char	**sort_array(char **to_sort, int iterations)
{
	int		i;
	int		j;
	int		swapped;
	char	*temp;

	i = -1;
	while (++i < iterations - 1)
	{
		swapped = 0;
		j = -1;
		while (++j < iterations - i - 1)
		{
			if (ft_strcmp(to_sort[j], to_sort[j + 1]) > 0)
			{
				temp = to_sort[j];
				to_sort[j] = to_sort[j + 1];
				to_sort[j + 1] = temp;
				swapped = 1;
			}
		}
		if (swapped == 0)
			break ;
	}
	return (to_sort);
}

//prints env variables in this form: "declare -x VAR = "value"""
void	print_env(char *env)
{
	int	i;

	i = 0;
	ft_putstr("declare -x ");
	while (env[i] && env[i] != '=')
	{
		ft_putchar(env[i]);
		i++;
	}
	if (env[i] == '=')
	{
		ft_putstr("=\"");
		i++;
		while (env[i])
		{
			ft_putchar(env[i]);
			i++;
		}
		ft_putchar('\"');
	}
	ft_putchar('\n');
}

//allocates far and makes a copy of envp with copy_char_array
//sorts strings alphabetically with sort_array
//prints each str with print_env
//then frees the created str array
//returns 1 on success, 0 on failure
int	export_no_arg(char **envp)
{
	int		i;
	int		str_num;
	char	**env_arr_sorted;

	i = 0;
	str_num = count_env_variables(envp);
	env_arr_sorted = malloc((str_num + 1) * sizeof(char *));
	if (!env_arr_sorted)
		return (0);
	env_arr_sorted = copy_str_array(envp, env_arr_sorted);
	if (env_arr_sorted == NULL)
	{
		free_str_array(env_arr_sorted);
		return (0);
	}
	env_arr_sorted = sort_array(env_arr_sorted, str_num);
	while (env_arr_sorted[i])
	{
		print_env(env_arr_sorted[i]);
		i++;
	}
	free_str_array(env_arr_sorted);
	return (1);
}

int	ft_export(char **command, t_mini *mini)
{
	if (command == NULL || command[0] == NULL)
		return (0);
	if (command[1] == NULL)
		return (export_no_arg(mini->envp));
	else
		return (export_with_arg(command, mini));
}
