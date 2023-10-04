/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:28:44 by nschutz           #+#    #+#             */
/*   Updated: 2023/09/27 14:53:41 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cmds(char **s, int *type)
{
	int	i;

	i = 0;
	while(s[i])
	{
		ft_printf("Array: %s\n Type: %i\n\n", s[i], type[i]);
		i++;
	}
}

int	count_alloc(t_input *input)
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

void sort_array(t_input **input, char **envp)
{
	char	**s;
	char	*tmp;
	int		*type;
	int		count;

	s = ft_calloc(count_alloc(*input) + 1, sizeof(char *));
	count = 0;
	tmp = NULL;
	type = malloc((count_alloc(*input) + 1) * sizeof(int));
	while (*input)
	{
		if ((*input)->type == COMMAND)
		{
			tmp = (*input)->word;
			*input = (*input)->next;
			type[count] = 5;
		}
		else if((*input)->type == BUILTIN)
		{
			tmp = (*input)->word;
			*input = (*input)->next;
			type[count] = 6;
		}
		else
			type[count] = 5;
		while (*input && (*input)->type != COMMAND && (*input)->type != BUILTIN)
		{
			if ((*input)->type == REDIRECT)
			{
				if (tmp != NULL)
				{
					s[count] = tmp;
					tmp = NULL;
					count++;
				}
				if (!ft_strncmp((*input)->word, "<", 1))
					type[count] = 1;
				else if (!ft_strncmp((*input)->word, "<<", 1))
					type[count] = 2;
				else if (!ft_strncmp((*input)->word, ">", 1))
					type[count] = 3;
				else if (!ft_strncmp((*input)->word, ">>", 1))
					type[count] = 4;
				else
					perror("Invalid redirect");
			}
			else if ((*input)->type == PIPE)
			{
				s[count] = tmp;
				tmp = NULL;
				count++;
			}
			else if ((*input)->type == FLAGS || (*input)->type == FILE || (*input)->type == PARAM)
				tmp = mod_strjoin(tmp, (*input)->word);
			(*input) = (*input)->next;
		}
	}
	s[count] = tmp;
	print_cmds(s, type);
	execute(type, s, envp);
	free_array(s);
	free(type);
}
