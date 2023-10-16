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

static char	*quotes(char *s, char c)
{
	char	*ret;
	int 	i;
	int		j;

	ret = ft_substr(s, 1, ft_strlen(s) - 2);
	i = 0;
	j = 0;
	while (ret[i])
	{
		if (ret[i] == c)
		{
			ret = modified_strjoin(ft_substr(ret, 0, i - 1), ft_substr(ret, i + 1, ft_strlen(ret - i)));
			j++;
		}
		i++;
	}
	if (j%2 != 0)
	{
		ft_putstr_fd("Open Quotes", 0);
		free(ret);
		return (NULL);
	}
	return (ret);
}

static char	*env_var(char *s, char **envp, int *l_r)
{
	int		i;
	int 	j;
	int 	k;
	char	*dup;

	i = 0;
	j = 0;
	while (s[i] != '$')
		i++;
	dup = ft_calloc(i + 1, 1);
	while (j < i)
	{
		dup[j] = s[j];
		j++;
	}
	if (dup[j - 1] == 39)
		j = 1;
	else
		j = 0;
	if (!ft_strncmp(&s[i], "$?", 3))
		dup = modified_strjoin(dup, ft_itoa(*l_r));
	else
	{
		k = i;
		while (s[k] &&  s[k] != 39)
			k++;
		dup = modified_strjoin(dup, mod_get_env(envp, &s[i + 1], j, &s[k]));
	}
	return (dup);
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
		new->word = quotes(s, s[0]);
		if (!new->word)
			return (NULL);
		if (is_env_var(s))
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

int	input_sort(char *line, char ***envp, int *l_r)
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
	linked_list_start(cmd, *envp, &input, l_r);
	r = sort_array(&input, &array);
	free_list(&input);
	return (r);
}
