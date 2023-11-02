/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:02:33 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/02 14:48:49 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char				**new_env;
	char				*line;
	int					last_return;
	struct sigaction			sa;

	set_sig_handle_prompt(&sa);
	turn_off_ctl_echo();
	g_signal = 0;
	if (argc && argv)
		argc = 1;
	new_env = dup_array(envp); //leak
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
		set_sig_handle_executer(&sa);
		last_return = input_sort(line, &new_env, last_return);
		if (last_return == -1)
		{
			free_array(new_env);
			free(line);
			return (-1);
		}
		g_signal = 0;
		set_sig_handle_prompt(&sa);
		free(line);
	}
	return (0);
}
