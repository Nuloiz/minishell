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

static int	count_alloc(t_array **array)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while ((*array)->cmds[j] != NULL)
	{
		if ((*array)->pipe[j] == 0 || k == 1)
		{
			k = 0;
			j++;
		}
		else
		{
			k = 1;
			i++;
		}
	}
	return (i);
}

static int	sort_commands(t_command **token, t_array **array, int *i, int j)
{
	if ((*array)->pipe[j] == 0)
	{
		if (token[*i]->type != 5 && token[*i]->type != 6)
			token[*i]->type = (*array)->type[j];
		if ((*array)->type[j] == 1)
			token[*i]->input = (*array)->cmds[j];
		else if ((*array)->type[j] == 2)
			token[*i]->limiter = (*array)->cmds[j];
		else if ((*array)->type[j] == 3)
			token[*i]->output = (*array)->cmds[j];
		else if ((*array)->type[j] == 4)
		{
			token[*i]->output = (*array)->cmds[j];
			token[*i]->append = 1;
		}
		else
			token[*i]->command = (*array)->cmds[j];
		j++;
	}
	else
	{
		(*array)->pipe[j] = 0;
		*i = *i + 1;
	}
	return (j);
}

t_command	**get_commands(t_array **array)
{
	t_command	**token;
	int			i;
	int			j;
	int			alloc;

	i = 0;
	j = 0;
	alloc = count_alloc(array) + 1;
	token = ft_calloc(sizeof(t_command *), alloc + 1); //leak (72 in 1 def lost && 16 still reach)
	if (!token)
		return (NULL);
	while (i < alloc)
	{
		token[i] = ft_calloc(sizeof(t_command), 1); //56 in 1 indir lost && 56 in  1 still reach && 56 bytes alloced but only 8 used)
		if (!token[i])
			return (free_command(token, i), NULL);
		i++;
	}
	token[i] = NULL;
	i = 0;
	while ((*array)->cmds[j] != NULL)
	{
		token[i]->index = i;
		j = sort_commands(token, array, &i, j);
	}
	return (token);
}
