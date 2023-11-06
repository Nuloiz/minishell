/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:02:33 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/06 05:58:37 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int argc, char **argv, char **envp)
{
	char				**new_env;
	char				*line;
	int					last_return;

	set_sig_handle_prompt();
	turn_off_ctl_echo();
	g_signal = 0;
	if (argc && argv)
		argc = 1;
	new_env = dup_array(envp);
	if (!new_env)
		return (-1);
	last_return = 0;
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
		{
			// rl_replace_line("minishell: exit", 0);
			printf("exit\n");
			free_array(new_env);
			free(line);
			break ;
		}
		add_history(line);
		// set_sig_handle_executer(&sa);
		set_sig_handle_executer();
		last_return = input_sort(line, &new_env, last_return);
		if (last_return == -1)
		{
			free_array(new_env);
			free(line);
			return (-1);
		}
		g_signal = 0;
		// set_sig_handle_prompt(&sa);
		set_sig_handle_prompt();
		free(line);
	}
	return (0);
}
