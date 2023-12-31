/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:28:44 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/04 15:40:56 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_alloc(t_input *input)
{
	int	count;

	count = 0;
	if (!input)
		return (0);
	while (input)
	{
		if ((input)->type == PIPE || (input)->type == REDIRECT)
			count++;
		input = (input)->next;
	}
	return (count + 1);
}

static char	*is_cmd(t_input **input, t_array array, int count)
{
	char	*tmp;

	tmp = NULL;
	if ((*input)->type == COMMAND)
	{
		tmp = (*input)->word;
		*input = (*input)->next;
		array.type[count] = 5;
	}
	else if ((*input)->type == BUILTIN)
	{
		tmp = (*input)->word;
		*input = (*input)->next;
		array.type[count] = 6;
	}
	else
		array.type[count] = 5;
	return (tmp);
}

static t_array	*fill_array(t_input *input, t_array *array, int *i, int *count)
{
	char		*tmp;

	while (input)
	{
		tmp = is_cmd(&input, *array, *count);
		*i = fill_tmp(&input, *array, count, &tmp);
		if (*i == 258)
			return (NULL);
		if (input && (input)->type == PIPE)
		{
			free((input)->word);
			(input) = (input)->next;
			array->pipe[(*count) + 1] = 1;
		}
		else
			array->pipe[(*count) + 1] = 0;
		array->cmds[(*count)] = tmp;
		*count = *count + 1;
	}
	return (array);
}

static t_array	*array_alloc(t_input *input, t_array *array)
{
	array->cmds = ft_calloc(count_alloc(input) + 1, sizeof(char *));
	if (!array->cmds)
		return (NULL);
	array->type = malloc((count_alloc(input) + 2) * sizeof(int));
	if (!array->type)
	{
		free(array->cmds);
		return (array);
	}
	array->pipe = malloc((count_alloc(input) + 2) * sizeof(int));
	if (!array->pipe)
	{
		free(array->cmds);
		free(array->type);
		return (array);
	}
	array->pipe[0] = 0;
	return (array);
}

int	sort_array(t_input *input, t_array	*array)
{
	t_command	**token;
	int			count;
	int			i;
	int			r;

	array = array_alloc(input, array);
	if (!array)
		return (-1);
	count = 0;
	i = 0;
	array = fill_array(input, array, &i, &count);
	if (i == 258)
		return (258);
	if (!array)
		return (-1);
	array->type[count] = 0;
	array->pipe[count] = 0;
	token = get_commands(&array);
	free_list(&input);
	if (!token)
		return (-1);
	r = execute(array->envp, token);
	return (r);
}
