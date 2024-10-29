/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:59:26 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 14:52:59 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

//happens when ctrl + C pressed
//interrupts current foreground process
//clears current input line wiht rl_replace_line
//displays new prompt with rl_on_new_line and rl_redisplay
static void	signal_interrupt(int sig)
{
	(void)sig;
	g_signal_status = 130;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	//rl_redisplay();
}

//should interupt any command running?
void	ft_signal_setup(void)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, SIG_IGN);
}
//need a handler for ctrl-\?
//in subject: ctrl-\ does nothing