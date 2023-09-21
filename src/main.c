/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:19:04 by nschutz           #+#    #+#             */
/*   Updated: 2023/09/21 12:51:27 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void	ft_sig_handle(int sig)
{
	if (sig == 2)
	{
		// rl_replace_line("", 0);
		// printf("signal: %i caught! i will be a new promt on new line\n", sig);
		// printf("minishell after signal2-0.1$ ");
		// 
		rl_replace_line("hello", 0);
		write(0, "\n", 2);
		rl_on_new_line();
		rl_redisplay();
		// readline, rl_clear_history, rl_on_new_line,
		// rl_replace_line, rl_redisplay
	}
	else
		printf("signal: %i caught!\n", sig);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	char				*line;

	sa.sa_handler = &ft_sig_handle;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	rl_replace_line("hello", 1);
	rl_redisplay();
	line = readline(0);
	// while (1)
	// {
	// 	if (!line)
	// 	{
	// 		write(0 , "exit\n", 6);
	// 		// rl_on_new_line();
	// 		// rl_replace_line("exit", 0);
	// 	}
	// 	if (line && !ft_strncmp(line, "exit", 4))
	// 		break ;
	// 	// printf("minishell-0.1$ ");
	// 	line = readline(0);
	// 	if (!line)
	// 		add_history("");
	// 	else
	// 		add_history(line);
	// }
	
	// sigaction, sigemptyset, sigaddset
	// signal
	//input_sort(line, envp);
	//free(line);
	rl_replace_line("hello", 1);
	rl_redisplay();
	line = readline(0);
	return (0);
}
