/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:15:38 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/03 14:22:11 by dnebatz          ###   ########.fr       */
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

void	set_sig_handle_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
