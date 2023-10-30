/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:16:52 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/30 16:46:41 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_from_token(t_execute *new, t_command **token)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		// dprintf(2, "token[%i]->type: %i\n", i, token[i]->type);
		if (token[i]->limiter)
			new->count_limiter ++;
		if (token[i]->type == 5)
			new->count_commands ++;
		if (token[i]->type == 6)
			new->count_builtins ++;
		if (token[i]->type >= 1 && token[i]->type <= 4)
			new->count_only_files ++;
	}
}

int	ft_init_struct(t_execute *new, t_command **token, char ***envp)
{
	new->count_commands = 0;
	new->count_builtins = 0;
	new->count_limiter = 0;
	new->count_only_files = 0;
	ft_init_from_token(new, token);
	new->count_children = new->count_commands + new->count_builtins + new->count_only_files;
	new->id = malloc(sizeof(int) * (new->count_children));
	new->count_pipes = new->count_children - 1;
	if (token[0]->limiter)
		new->count_pipes++;
	if (new->count_pipes < 1)
		new->count_pipes = 1;
	new->pipe_fd = malloc(sizeof(int *) * (new->count_pipes));
	new->error = 0;
	new->envp = envp;
	new->token = token;
	return (1);
}
