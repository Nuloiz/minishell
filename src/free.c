/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:55:58 by nschutz           #+#    #+#             */
/*   Updated: 2023/09/19 10:55:58 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_list(t_input **input)
{
	t_input	*tmp;

	while (*input)
	{
		tmp = *input;
		*input = tmp->next;
		free(tmp);
	}
	free(*input);
}

void	free_command(t_command **token, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free(token[i]);
		i++;
	}
	free(token);
}
