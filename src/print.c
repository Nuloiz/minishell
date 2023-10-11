/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:19:07 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/11 10:19:07 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_input **input)
{
	while (*input)
	{
		ft_printf("Word: %s\n", (*input)->word);
		*input = (*input)->next;
	}
}

void	print_cmds(char **s, int *type)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		ft_printf("Array: %s\n Type: %i\n\n", s[i], type[i]);
		i++;
	}
}

