/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:30:24 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 12:30:27 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_flag_signal == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			write(1, "\n", 1);
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
}

static void	quit_handler(int sig)
{
	(void)sig;
	if (rl_line_buffer && rl_line_buffer[0] != '\0')
	{
		write(1, "\nexit\n", 6);
		exit(0);
	}
}

/*
	SIGINT (Ctrl+C) -> signal_handler
	SIGQUIT (Ctrl+\) ->  quit_handler
*/
void	handle_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	sa_int.sa_handler = signal_handler;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = quit_handler;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
