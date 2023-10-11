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

static char	*quotes(char *s)
{
	char	*ret;

	ret = ft_substr(s, 1, ft_strlen(s) - 2);
	return (ret);
}

static char	*env_var(char *s, char **envp, int *l_r)
{
	if (!ft_strncmp(s, "$?", 3))
		s = ft_itoa(*l_r);
	else
		s = ft_get_env(envp, &s[1]);
	return (s);
}

static t_input	*new_node(char *s, char *s_one, char **envp, int *l_r)
{
	t_input	*new;

	new = ft_calloc(1, sizeof(t_input));
	if (!new)
		return (NULL);
	new->type = input_type(s, s_one, envp);
	if (s[0] == 34 || s[0] == 39)
	{
		new->word = quotes(s);
		if (!new->word)
			return (NULL);
		if (s[0] == 34 && is_env_var(&s[1]))
			new->type = 4;
	}
	else
		new->word = s;
	if (new->type == 4)
	{
		new->word = env_var(new->word, envp, l_r);
		free(s);
	}
	new->next = NULL;
	return (new);
}

static t_input	**linked_list_start(char **cmd, char **envp, \
									t_input **input, int *l_r)
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
		if (i == 0)
			new = new_node (cmd[0], NULL, envp, l_r);
		else
			new = new_node(cmd[i], cmd[i - 1], envp, l_r);
		if (!new)
			return (NULL);
		mod_lstadd_back(input, new);
		i++;
	}
	free(cmd);
	return (input);
}

void	print_list(t_input **input)
{
	while (*input)
	{
		ft_printf("Word: %s\n", (*input)->word);
		*input = (*input)->next;
	}
}

int	input_sort(char *line, char **envp, int *l_r)
{
	t_input	*input;
	t_array	array;
	char	**cmd;
	int		r;

	input = NULL;
	array.envp = envp;
	if (!line)
		return (0);
	cmd = mod_split(line, ' ');
	linked_list_start(cmd, envp, &input, l_r);
	r = sort_array(&input, &array);
	print_list(&input);
	free_list(&input);
	return (r);
}
