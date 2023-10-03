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

void check_cmds(char **array, int *type, int stop, char **envp)
{
	int		i;
	char	*s;

	i = 0;
	while (i < stop)
	{
		if (type[i] == 5)
		{
			if (!find_path(array[i], envp))
				perror("Invalid Command");
		}
		else if (type[i] != 6)
		{
			if (!is_file(array[i]))
				perror("Invalid filename");
		}
		i++;
	}
}

char	**skip(char **array, int *type, char **envp)
{
	int		i;
	int 	j;

	i = 0;
	j = 0;
	while (array[i])
	{
		if (type[i] == 6)
			j = i;
		i++;
	}
	if ((j == 0 && type[0] != 6) || !ft_strncmp(array[j], "echo", 4) || !ft_strncmp(array[j], "envp", 4))
		i = -1;
	if (array[j + 1] && (type[j + 1] == 5 || type[j + 1] == 6) && i > -1)
		j++;
	ft_printf("new Array:\n");
	print_cmds(&array[j], &type[j]);
	check_cmds(array, type, j, envp);
	return (&array[j]);
}

int	count_alloc(t_input *input)
{
	int	count;

	count = 0;
	if (!input)
		return (0);
	while (input)
	{
		if (input->type == PIPE || input->type == REDIRECT)
			count++;
		input = input->next;
	}
	return (count + 1);
}
void sort_array(t_input *input, char **envp)
{
	char	**s;
	char	*tmp;
	int		*type;
	int		count;

	s = ft_calloc(count_alloc(input) + 1, sizeof(char **));
	count = 0;
	tmp = NULL;
	type = malloc((count_alloc(input) + 1) * sizeof(int));
	while (input)
	{
		if (input->type == COMMAND)
		{
			tmp = input->word;
			input = input->next;
			type[count] = 5;
		}
		else if(input->type == BUILTIN)
		{
			tmp = input->word;
			input = input->next;
			type[count] = 6;
		}
		else
			type[count] = 5;
		while (input && input->type != COMMAND && input->type != BUILTIN)
		{
			if (input->type == REDIRECT)
			{
				if (tmp != NULL)
				{
					s[count] = tmp;
					tmp = NULL;
				}
				count++;
				if (!ft_strncmp(input->word, "<", 1))
					type[count] = 1;
				else if (!ft_strncmp(input->word, "<<", 1))
					type[count] = 2;
				else if (!ft_strncmp(input->word, ">", 1))
					type[count] = 3;
				else if (!ft_strncmp(input->word, ">>", 1))
					type[count] = 4;
				else
					perror("Invalid redirect");
			}
			else if (input->type == PIPE)
			{
				s[count] = tmp;
				tmp = NULL;
				count++;
			}
			else if (input->type == FLAGS || input->type == FILE || input->type == PARAM)
				tmp = mod_strjoin(tmp, input->word);
			input = input->next;
		}
	}
	s[count] = tmp;
	print_cmds(s, type);
	skip(s, type, envp);
}