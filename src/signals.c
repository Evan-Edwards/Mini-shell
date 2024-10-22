/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:59:26 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/22 10:05:20 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//happens when ctrl + C pressed
//interrupts current foreground process
//clears current input line wiht rl_replace_line
//displays new prompt with rl_on_new_line and rl_redisplay
static void	signal_interrupt(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	//having errors when trying to check for return of rl_replace_line
	if (rl_on_new_line() != 0)
		ft_error_close("read_line");
	rl_redisplay();
}

//happens when ctrl + \.
//Used for child functions 
//????
static void	ft_signal_quit()
{
	
}
//should interupt any command running?



void	ft_signal_setup()
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, ft_signal_quit);
}
//need a handler for ctrl-\?
//in subject: ctrl-\ does nothing