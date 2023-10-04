/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:35:06 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/02 16:23:23 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_list(t_input **input)
{
	while (*input)
	{
		ft_printf("Word: %s\n", (*input)->word);
		*input = (*input)->next;
	}
}

int	sort_tree(t_input **input, char **envp)
{
	sort_array(input, envp);
	print_list(input);
	free_list(input);
	print_list(input);
	return (1);
}
