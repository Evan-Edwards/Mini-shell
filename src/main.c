/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:24:50 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 09:41:28 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if readline returns null it indicates Ctrl-D/ EOF, causing end of program
int	main(int ac, char *av[], char **envp)
{
	char		*input;
	t_mini		mini;

	ft_signal_setup();
	mini.envp = envp;
	mini.history = NULL;
	mini.in = dup(STDIN_FILENO);
	mini.out = dup(STDOUT_FILENO);
	mini.ret_value = 0;
	while (ac && av)
	{
		input = readline("Input > ");
		if (input == NULL)
			ft_close(input, NULL, &mini);
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		if (ft_history(input, &mini) == 0)
			ft_error_close(input, NULL, &mini);
		input_to_tokens(input, &mini);
		//print_list(&mini);
		if (check_errors(mini.lst) == 0) //?
			continue ;
		set_types(mini.lst);
		dis_b(&mini);
		free(input);
	}
	return (0);
}
