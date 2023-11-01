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

static char	*end_of_quote(char *ret, int *i, int *j, char c)
{
	char	*tmp;

	if (ret[*i] == c)
	{
		tmp = modified_strjoin(ft_substr(ret, 0, *i), \
			ft_substr(ret, (*i) + 1, ft_strlen(ret) - *i));
		free(ret);
		if (!tmp)
			return (NULL);
		ret = tmp;
		*i = *i - 2;
		*j = *j + 1;
	}
	*i = *i + 1;
	return (ret);
}

static char	*quotes(char *s, char c)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_substr(s, 1, ft_strlen(s) - 2);
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (ret[i] != '\0')
	{
		ret = end_of_quote(ret, &i, &j, c);
		if (!ret)
			return (NULL);
	}
	if (j % 2 != 0)
	{
		ft_putstr_fd("Open Quotes", 0);
		free(ret);
		return (NULL);
	}
	return (ret);
}

static t_input	*found_quote(t_input *new, char **s)
{
	char 	*tmp;
	int 	i;

	i = 0;
	while ((*s)[i] && (*s)[i] != 34 && (*s)[i] != 39)
		i++;
	tmp = ft_substr(*s, 0, i);
	if (!tmp && i > 0)
		return (NULL);
	new->word = quotes(&(*s)[i], (*s)[i]);
	if (!new->word)
		return (NULL);
	new->word = mod_nocheck_strjoin(tmp, new->word);
	if (!new->word)
		return (NULL);
	if (is_env_var(*s))
		new->type = 4;
	free(*s);
	*s = new->word;
	return (new);
}
static t_input	*new_node(char **s, char *s_one, char **envp, int *l_r)
{
	t_input	*new;

	new = ft_calloc(1, sizeof(t_input));
	if (!new)
		return (NULL);
	new->type = input_type(*s, s_one, envp);
	if (ft_strchr(*s, 39) || ft_strchr(*s, 34))
	{
		new = found_quote(new, s);
		if (!new)
			return (NULL);
	}
	else
		new->word = *s;
	if (new->type == 4)
	{
		new->word = env_var(new->word, envp, l_r);
		if (!new->word)
			return (NULL);
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
			new = new_node (&cmd[0], NULL, envp, l_r);
		else
			new = new_node(&cmd[i], cmd[i - 1], envp, l_r);
		if (!new)
			return (NULL);
		mod_lstadd_back(input, new);
		i++;
	}
	free(cmd);
	return (input);
}

int just_space(char *line)
{
	int i;

	i = 0;
	while (line[i] && isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

int	input_sort(char *line, char ***envp, int *l_r)
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
		return (-1);
	linked_list_start(cmd, *envp, &input, l_r);
	if (!input)
	{
		free_list(&input);
		return (-1);
	}
	r = sort_array(&input, &array);
	free_list(&input);
	return (r);
}
