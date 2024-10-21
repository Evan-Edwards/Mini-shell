/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:24:50 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/21 14:57:15 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




//if readline returns null it indicates Ctrl-D/ EOF, causing end of program
int main (int ac, char *av[], char **envp)
{
	char	*input;
	t_mini	mini;

	//take input
	input = readline("Input > ");
	if (input == NULL)
		ft_close();
	//lex input, put them into tokens
	input = re_main(input, envp);
	mini = ct_main(input);
	//error handling?
	//parse tokens
	//build into command table
	free(input);
	//execute command table
	//wait for next command?
	ft_signal_setup();
	//close program, free memory
	

}

//There is at least making the program open and close properly, 
//and the ctrl commands, or you can do any of the build in functions