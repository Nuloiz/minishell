/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:16:52 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/18 11:25:53 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_from_token(t_execute *new, t_command **token)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		dprintf(2, "token[%i]->type: %i\n", i, token[i]->type);
		if (token[i]->type == 2)
			new->count_limiter ++;
		if (token[i]->type == 5)
			new->count_commands ++;
		if (token[i]->type == 6)
			new->count_builtins ++;
	}
}

int	ft_init_struct(t_execute *new, t_command **token, char ***envp)
{
	new->input = NULL;
	new->append = 0;
	new->output = NULL;
	new->limiter = NULL;
	new->count_commands = 0;
	new->count_builtins = 0;
	new->count_limiter = 0;
	ft_init_from_token(new, token);
	new->count_children = new->count_commands + new->count_builtins;
	new->id = malloc(sizeof(int) * (new->count_children));
	new->count_pipes = new->count_children - 1;
	if (new->count_limiter)
		new->count_pipes++;
	if (new->count_pipes < 1)
		new->count_pipes = 1;
	new->pipe_fd = malloc(sizeof(int *) * (new->count_pipes));
	new->error = 0;
	new->envp = envp;
	new->token = token;
	return (1);
}
