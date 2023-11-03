/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:36:43 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/03 10:36:06 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_handle_prompt(int sig)
{
	if (sig == 2)
	{
		g_signal = 2;
		rl_replace_line("", 0);
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
	}
	else if (sig == 3)
	{
		g_signal = 3;
		printf("Quit: 3\n");
	}
}

void	ft_sig_handle_execute(int sig)
{
	if (sig == 2)
		g_signal = 2;
	else if (sig == 3)
	{
		g_signal = 3;
		printf("Quit: 3\n");
	}
}

void	sig_handle_executer(int sig)
{
	if (sig == 2)
	{
		g_signal = 2;
	}
	else if (sig == 3)
		g_signal = 3;
	else
		printf("signal: %i caught!\n", sig);
}

// void	set_sig_handle_executer(struct sigaction *sa)
// {
// 	sa->sa_handler = &ft_sig_handle_execute;
// 	sa->sa_flags = SA_RESTART;
// 	sigaction(SIGINT, sa, NULL);
// 	sigaction(SIGQUIT, sa, NULL);
// }

// void	set_sig_handle_prompt(struct sigaction *sa)
// {
// 	sa->sa_handler = &ft_sig_handle_prompt;
// 	sa->sa_flags = SA_RESTART;
// 	sigaction(SIGINT, sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	set_sig_handle_executer(void)
{
	signal(SIGINT, ft_sig_handle_execute);
	signal(SIGQUIT, ft_sig_handle_execute);
}

void	set_sig_handle_prompt(void)
{
	signal(SIGINT, ft_sig_handle_prompt);
	signal(SIGQUIT, SIG_IGN);
}
