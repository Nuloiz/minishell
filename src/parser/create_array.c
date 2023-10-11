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

static int	type_redirect(t_input **input, t_array array, int *count)
{
	int	i;

	i = 0;
	if (!ft_strncmp((*input)->word, "<", 2))
	{
		array.type[*count] = 1;
		i = 2;
	}
	else if (!ft_strncmp((*input)->word, "<<", 3))
	{
		array.type[*count] = 2;
		i = 2;
	}
	else if (!ft_strncmp((*input)->word, ">", 2))
		array.type[*count] = 3;
	else if (!ft_strncmp((*input)->word, ">>", 3))
		array.type[*count] = 4;
	else
		perror("Invalid redirect");
	return (i);
}

static char	*fill_tmp(t_input **input, t_array array, int *count, char *tmp)
{
	int	i;

	i = 0;
	while (*input && (*input)->type != PIPE && i != 1)
	{
		if ((*input)->type == REDIRECT)
		{
			if (tmp != NULL)
			{
				array.cmds[*count] = tmp;
				tmp = NULL;
				(*count)++;
			}
			i = type_redirect(input, array, count);
		}
		else
		{
			tmp = mod_strjoin(tmp, (*input)->word);
			i--;
		}
		(*input) = (*input)->next;
	}
	return (tmp);
}

int	sort_array(t_input **input, t_array	*array)
{
	char	*tmp;
	int		count;
	int		r;

	array->cmds = ft_calloc(count_alloc(*input) + 1, sizeof(char *));
	count = 0;
	array->type = malloc((count_alloc(*input) + 2) * sizeof(int));
	while (*input)
	{
		tmp = is_cmd(input, *array, count);
		tmp = fill_tmp(input, *array, &count, tmp);
		if (*input && (*input)->type == PIPE)
			(*input) = (*input)->next;
		array->cmds[count] = tmp;
		count++;
	}
	array->type[count] = 0;
	print_cmds(array->cmds, array->type);
	r = execute(array->type, array->cmds, array->envp);
	free(array->type);
	return (r);
}
