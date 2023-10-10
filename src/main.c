/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:19:04 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/10 13:41:13 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <unistd.h>
// #include <signal.h>
// #include <stdio.h>
// #include "executer/pipex.h"

// void	ft_sig_handle(int sig)
// {
// 	if (sig == 2)
// 	{
// 		// rl_replace_line("", 0);
// 		// printf("signal: %i caught! i will be a new promt on new line\n", sig);
// 		// printf("minishell after signal2-0.1$ ");
// 		// 
// 		rl_replace_line("hello\n", 0);
// 		// write(0, "\n", 2);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		// readline, rl_clear_history, rl_on_new_line,
// 		// rl_replace_line, rl_redisplay
// 	}
// 	else
// 		printf("signal: %i caught!\n", sig);
// }

int	main(int argc, char **argv, char **envp)
{
	char				**new_env;
	char				*line;

	// sa.sa_handler = &ft_sig_handle;
	// sa.sa_flags = SA_RESTART;
	// sigaction(SIGINT, &sa, NULL);
	// signal(SIGQUIT, SIG_IGN);
	// rl_replace_line("hello", 1);
	// rl_redisplay();
	new_env = dup_array(envp);
	line = readline(0);
	add_history(line);
	while (line)
	{
		if (line[0] == '\0')
			break ;
		input_sort(line, new_env);
		free(line);
		line = readline(0);
		add_history(line);
	}
	free(line);
	return (0);
}
