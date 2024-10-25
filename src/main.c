/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:24:50 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/25 13:38:29 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//if readline returns null it indicates Ctrl-D/ EOF, causing end of program
int main (int ac, char *av[], char **envp)
{
	char	*input;
	t_mini	mini; //malloc for mini?

	(void)ac;
	(void)av;
	ft_signal_setup();
	while (1)
	{
		input = readline("Input > ");
		if (input == NULL)
			ft_close();
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		input_to_tokens(input, envp, &mini);
		print_list(&mini);
		//error handling?
		//parse tokens
		//build into command table
		free(input);
		//execute command table
		//wait for next command?
	}
	//close program, free memory
	return (0);
	

}

//There is at least making the program open and close properly, 
//and the ctrl commands, or you can do any of the build in functions