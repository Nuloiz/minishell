/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:26:55 by nschutz           #+#    #+#             */
/*   Updated: 2023/09/23 10:41:39 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_input	*new_node(char **s, char **envp, int l_r)
{
	int		i;
	int		j;
	t_input	*new;

	i = 0;
	j = 0;
	new = ft_calloc(1, sizeof(t_input));
	if (!new)
		return (NULL);
	new->type = input_type(*s, envp);
	if (ft_strchr(*s, 39) || ft_strchr(*s, 34))
	{
		while ((*s)[i] != 39 && (*s)[i] != 34)
			i++;
		if ((*s)[i] == 39)
			j = 1;
		new = found_quote(new, s, (*s)[i]);
		if (!new)
			return (NULL);
	}
	else
		new->word = *s;
	if (new->type == 4 && j == 0)
	{
		new->word = env_var(new->word, envp, l_r);
		if (!new->word)
			return (NULL);
	}
	new->next = NULL;
	return (new);
}

static t_input	**linked_list_start(char **cmd, char **envp, \
									t_input **input, int l_r)
{
	int		num;
	int		i;
	t_input	*new;

	num = 0;
	i = 0;
	while (cmd[num])
		num++;
	while (i < num)
	{
		new = new_node (&cmd[i], envp, l_r);
		if (!new)
			return (NULL);
		mod_lstadd_back(input, new);
		i++;
	}
	free(cmd);
	return (input);
}

int	just_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

int	input_sort(char *line, char ***envp, int l_r)
{
	t_input	*input;
	t_array	array;
	char	**cmd;
	int		r;

	input = NULL;
	array.envp = envp;
	if (!line || just_space(line))
		return (0);
	cmd = mod_split(line, ' ');
	if (!cmd)
		return (1);
	if (!ft_strncmp(cmd[0], "|", 2))
	{
		free_array(cmd);
		return (printf("minishell: syntax error near unexpected token `|'\n"), \
		258);
	}
	linked_list_start(cmd, *envp, &input, l_r);
	if (!input)
	{
		free_list(&input);
		return (-1);
	}
	r = sort_array(input, &array);
	return (r);
}
