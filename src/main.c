/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:24:50 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 22:12:12 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_duplicate(char **envp, char *var, int current_pos)
{
	int		i;
	char	*eq_pos1;
	char	*eq_pos2;
	size_t	name_len1;
	size_t	name_len2;

	eq_pos1 = ft_strchr(var, '=');
	if (!eq_pos1)
		return (0);
	name_len1 = eq_pos1 - var;

	// Start from current_pos - 1 and work backwards
	i = current_pos - 1;
	while (i >= 0)
	{
		eq_pos2 = ft_strchr(envp[i], '=');
		if (eq_pos2)
		{
			name_len2 = eq_pos2 - envp[i];
			if (name_len1 == name_len2 &&
				ft_strncmp(var, envp[i], name_len1) == 0)
			{
				return (1);
			}
		}
		i--;
	}
	return (0);
}

static char	**copy_env(char **envp)
{
	char	**new_env;
	int		i;
	int		j;

	// Count total variables first
	i = 0;
	while (envp[i])
		i++;

	// Allocate new array with full size initially
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);

	// Copy variables in reverse order, skipping duplicates
	i--;
	j = 0;
	while (i >= 0)
	{
		if (!is_duplicate(envp, envp[i], i))
		{
			new_env[j] = ft_strdup(envp[i]);
			if (!new_env[j])
			{
				while (--j >= 0)
					free(new_env[j]);
				free(new_env);
				return (NULL);
			}
			j++;
		}
		i--;
	}
	new_env[j] = NULL;
	return (new_env);
}

static void	init_mini(t_mini *mini, char **envp)
{
	mini->envp = copy_env(envp);
	if (!mini->envp)
		exit(EXIT_FAILURE);
	mini->history = NULL;
	mini->lst = NULL;
	mini->status = DEFAULT;
	mini->exit_status = 0;
	mini->in = dup(STDIN_FILENO);
	mini->out = dup(STDOUT_FILENO);
}

//if readline returns null it indicates Ctrl-D/ EOF, causing end of program
int	main(int ac, char *av[], char **envp)
{
	char		*input;
	t_mini		mini;

	ft_signal_setup();
	init_mini(&mini, envp);
	while (ac && av)
	{
		input = readline("Input > ");
		if (input == NULL)
			ft_close(0, input, NULL, &mini);
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		if (ft_history(input, &mini) == 0)
			ft_close(EXIT_FAILURE, input, NULL, &mini);
		if (input_to_tokens(input, &mini) == 0)
			ft_close(EXIT_FAILURE, input, NULL, &mini);
		set_types(mini.lst);
		if (check_errors(mini.lst) == 0)
		{
			reset_input(input, &mini);
			continue;
		}
		dis_b(&mini);
		reset_input(input, &mini);
	}
	return (0);
}
