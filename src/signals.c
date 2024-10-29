/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:59:26 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 19:24:17 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

//happens when ctrl + C pressed
//interrupts current foreground process
//clears current input line wiht rl_replace_line
//displays new prompt with rl_on_new_line
static void signal_interrupt(int sig)
{
    (void)sig;
    if (g_signal_status != 2)
    {
        g_signal_status = 0; // Signal main loop to handle interruption
        ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_done = 1;
    }
	else
		ft_printf("\n");
}
//should interupt any command running?
void	ft_signal_setup(void)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, SIG_IGN);
}
