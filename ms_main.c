/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:24:50 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/21 11:51:39 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (void)
{
	char	*input;
	t_mini	mini;

	//take input
	input = readline("Input > ");
	input = re_main(input); //NEED TO FIX
	//error handling for readline?
	//lex input, put them into tokens
	mini = ct_main(input);
	//error handling?
	//parse tokens
	//build into command table
	//execute command table

	

	free(input);
}

//There is at least making the program open and close properly, 
//and the ctrl commands, or you can do any of the build in functions