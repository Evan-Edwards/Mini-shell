/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:59:26 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/31 10:48:28 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

//happens when ctrl + C pressed
//interrupts current foreground process
//clears current input line wiht rl_replace_line
//displays new prompt with rl_on_new_line
static void	signal_interrupt(int sig)
{
	(void)sig;
	g_signal_status = 0;
	if (write(STDIN_FILENO, "\n", 1) == -1)
		return ;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

//sets up signal handling
void	ft_signal_setup(void)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, SIG_IGN);
}
