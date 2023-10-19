/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:14:06 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/19 09:18:59 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	not_the_same(int array, int token)
{
	if (array == 5 && (token != 5 && token != 6))
		return (0);
	else if (array == 6 && (token != 5 && token != 6))
		return (0);
	else if (array != 5 && array != 6)
		return (0);
	else
		return (1);
}

static int	count_alloc(t_array **array)
{
	int			i;
	int 		j;
	int 		token;

	i = 0;
	j = 0;
	token = 0;
	while ((*array)->cmds[j] != NULL)
	{
		if (not_the_same((*array)->type[j], token) == 0)
		{
			if (token != 5 && token != 6)
				token = (*array)->type[j];
			j++;
		}
		else
		{
			token  = 0;
			i++;
		}
	}
	return (i);
}

t_command	**get_commands(t_array **array)
{
	t_command	**token;
	int			i;
	int 		j;

	i = 0;
	j = 0;
	token = ft_calloc(sizeof(t_command *), count_alloc(array) + 2);
	while (i <= count_alloc(array))
	{
		token[i] = ft_calloc(sizeof(t_command), 1);
		i++;
	}
	token[i] = ft_calloc(sizeof(t_command), 1);
	token[i] = NULL;
	i = 0;
	while ((*array)->cmds[j] != NULL)
	{
		token[i]->index = i;
		if (not_the_same((*array)->type[j], token[i]->type) == 0)
		{
			if (token[i]->type != 5 && token[i]->type != 6)
				token[i]->type = (*array)->type[j];
			if ((*array)->type[j] == 1)
				token[i]->input = (*array)->cmds[j];
			else if ((*array)->type[j] == 2)
				token[i]->limiter = (*array)->cmds[j];
			else if ((*array)->type[j] == 3)
				token[i]->output = (*array)->cmds[j];
			else if ((*array)->type[j] == 4)
			{
				token[i]->output = (*array)->cmds[j];
				token[i]->append = 1;
			}
			else
				token[i]->command = (*array)->cmds[j];
			j++;
		}
		else
		{
			i++;
		}
	}
	return (token);
}