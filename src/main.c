/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:24:50 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 11:37:13 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_mini(t_mini *mini, char **envp)
{
	mini->envp = envp;
	mini->history = NULL;
	mini->lst = NULL;
	mini->status = DEFAULT;
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
		//print_list(&mini);
		set_types(mini.lst);
		if (check_errors(mini.lst) == 0) //?
			continue ;
		dis_b(&mini);
		free(input);
	}
	return (0);
}
