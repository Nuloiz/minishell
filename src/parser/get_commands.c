/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:14:06 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/06 11:25:53 by nschutz          ###   ########.fr       */
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

static void	fill_commands(t_command **token, t_array **array, int *i, int *j)
{
	char	**str;

	if (token[*i]->type != 5 && token[*i]->type != 6)
		token[*i]->type = (*array)->type[*j];
	if ((*array)->type[*j] == 1)
		str = &token[*i]->input;
	else if ((*array)->type[*j] == 2)
		str = &token[*i]->limiter;
	else if ((*array)->type[*j] == 3)
		str = &token[*i]->output;
	else if ((*array)->type[*j] == 4)
	{
		str = &token[*i]->output;
		token[*i]->append = 1;
	}
	else
		str = &token[*i]->command;
	if (!(*str))
		*str = ft_strdup((*array)->cmds[*j]);
	if (!*str)
		*j = -2;
	(*j)++;
}

static int	sort_commands(t_command **token, t_array **array, int *i, int j)
{
	if ((*array)->pipe[j] == 0)
		fill_commands(token, array, i, &j);
	else
	{
		(*array)->pipe[j] = 0;
		(*i)++;
	}
	return (j);
}

static void	set_index(t_command **token, t_array **array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*array)->cmds[j] != NULL)
	{
		token[i]->index = i;
		j = sort_commands(token, array, &i, j);
		if (j == -1)
			return (free_token(token));
	}
	free_array((*array)->cmds);
	free((*array)->pipe);
	free((*array)->type);
}

t_command	**get_commands(t_array **array)
{
	t_command	**token;
	int			i;
	int			alloc;

	i = -1;
	alloc = count_alloc(array) + 1;
	token = ft_calloc(sizeof(t_command *), alloc + 1);
	if (!token)
		return (NULL);
	while (++i < alloc)
	{
		token[i] = ft_calloc(sizeof(t_command), 1);
		if (!token[i])
			return (free_command(token, i), NULL);
	}
	token[i] = NULL;
	set_index(token, array);
	return (token);
}
