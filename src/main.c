/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:24:50 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/27 12:35:32 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



//if readline returns null it indicates Ctrl-D/ EOF, causing end of program
int main (int ac, char *av[], char **envp)
{
	char		*input;
	t_mini		mini; //malloc for mini?
	t_history	*history;

	(void)ac;
	(void)av;
	ft_signal_setup();
	history = NULL;
	while (1)
	{
		input = readline("Input > ");
		if (input == NULL)
			ft_close(input, history, &mini);
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		ft_history(input, history);
		input_to_tokens(input, envp, &mini);
		free(input);
		print_list(&mini);
		//if (check_errors(mini.lst) == 0) //?
				//continue;
		//set_types(mini.lst); //COMMENTED FOR MAKE
		//dis_b(&mini, envp); //COMMENTED FOR MAKE
		//error handling?
		//parse tokens
		//build into command table
		//execute command table
		//wait for next command?
	}
	//close program, free memory
	return (0);

}

