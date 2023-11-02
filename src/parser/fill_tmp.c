/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:27:17 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/24 11:27:17 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	type_redirect(t_input **input, t_array array, int *count)
{
	int	i;

	i = 2;
	if (!ft_strncmp((*input)->word, "<", 2))
		array.type[*count] = 1;
	else if (!ft_strncmp((*input)->word, "<<", 3))
		array.type[*count] = 2;
	else if (!ft_strncmp((*input)->word, ">", 2))
		array.type[*count] = 3;
	else if (!ft_strncmp((*input)->word, ">>", 3))
		array.type[*count] = 4;
	else
	{
		perror("Invalid redirect");
		i = 0;
	}
	return (i);
}

static void	redirect_after_param(t_array array, int *count, char **tmp)
{
	if (*tmp != NULL)
	{
		array.cmds[*count] = *tmp;
		*tmp = NULL;
		(*count)++;
		array.pipe[*count] = 0;
	}
}

int	fill_tmp(t_input **input, t_array array, int *count, char **tmp)
{
	int	i;

	i = 0;
	while (*input && (*input)->type != PIPE && i != 1)
	{
		if ((*input)->type == REDIRECT)
		{
			redirect_after_param(array, count, tmp);
			i = type_redirect(input, array, count);
		}
		else
		{
			*tmp = mod_strjoin(*tmp, (*input)->word); //leak
			if (!*tmp)
				return (-1);
			i--;
		}
		(*input) = (*input)->next;
		if (nv_after_red(input, i) == 258)
			return (258);
	}
	return (0);
}
