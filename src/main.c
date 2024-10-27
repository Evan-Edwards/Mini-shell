/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:24:50 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 13:22:12 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if readline returns null it indicates Ctrl-D/ EOF, causing end of program
int main (int ac, char *av[], char **envp)
{
	char		*input;
	t_mini		mini; //malloc for mini?

	(void)ac;
	(void)av;
	ft_signal_setup();
	mini.envp = envp;
	while (1)
	{
		input = readline("Input > ");
		if (input == NULL)
			ft_close(input, &mini);
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		ft_history(input, &mini);
		input_to_tokens(input, envp, &mini);
		free(input);
		print_list(&mini);
		//if (check_errors(mini.lst) == 0) //?
				//continue;
		//set_types(mini.lst); //COMMENTED FOR MAKE
		//distribute(&mini, envp); //COMMENTED FOR MAKE
		//parse tokens
	}
	//close program, free memory
	return (0);

}

