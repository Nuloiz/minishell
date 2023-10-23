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

void	print_cmds(char **s, int *type, int *pipe)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		ft_printf("Array: %s\n Type: %i\n Pipe: %i\n\n", \
				s[i], type[i], pipe[i]);
		i++;
	}
}

void	print_commands(t_command **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		printf("index: %i\n", token[i]->index);
		if (token[i]->command)
			printf("	command: %s\n", token[i]->command);
		if (token[i]->input)
			printf("	input: %s\n", token[i]->input);
		if (token[i]->output)
			printf("	output: %s\n", token[i]->output);
		if (token[i]->append)
			printf("	append: %i\n", token[i]->append);
		if (token[i]->limiter)
			printf("	limiter: %s\n", token[i]->limiter);
		if (token[i]->type)
			printf("	type: %i\n", token[i]->type);
		i++;
	}
}
