/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:36:43 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/01 18:58:57 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// turn off ECHOCTL flag
void	turn_off_ctl_echo(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	else if (isatty(STDOUT_FILENO))
	{
		tcgetattr(STDOUT_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	}
	else if (isatty(STDERR_FILENO))
	{
		tcgetattr(STDERR_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDERR_FILENO, TCSANOW, &term);
	}
}

// resets global and return exit
int	reset_signal(int exit_status)
{
	int	temp;

	temp = g_signal;
	g_signal = 0;
	if (!exit_status)
		return (exit_status);
	return (temp);
}

void	ft_sig_handle(int sig)
{
	if (sig == 2)
	{
		g_signal = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
		
		// readline, rl_clear_history, rl_on_new_line,
		// rl_replace_line, rl_redisplay
	}
	else if (sig == 3)
		g_signal = 3;
	else
		printf("signal: %i caught!\n", sig);
}
