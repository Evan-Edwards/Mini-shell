/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:24:50 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/28 06:14:11 by eedwards         ###   ########.fr       */
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
	while (ac && av)
	{
		input = readline("Input > ");
		if (input == NULL)
			ft_close(input, &mini);
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		//ft_history(input, &mini); //segfaults
		input_to_tokens(input, &mini);
		//free(input);
		//print_list(&mini);
		if (check_errors(mini.lst) == 0) //?
			continue ;
		set_types(mini.lst);
		dis_b(&mini);
		free(input);
	}
	return (0);
}
