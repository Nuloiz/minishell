/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command_arg_array.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:32:28 by dnebatz           #+#    #+#             */
/*   Updated: 2023/09/19 17:51:23 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//"grep Hello", "awk '{count++} END {print count}'"
//"grep -v !", "sed 's/Hello/Salut/g'"

void	ft_remove(char *start, char *end)
{
	ft_memmove(start, end, (end - start) / sizeof(char));
}

int	ft_strchr_count(const char *string, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (string == NULL)
		return (0);
	while (string[i])
	{
		if (string[i] == c)
			j++;
		i++;
	}
	return (j);
}

int	ft_get_pos(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	**ft_delete_char_and_split(char *command, char c)
{
	unsigned int	size;
	int				pos;
	char			**command_array;
	char			*deleted;

	size = (ft_strrchr(command, c)
			- ft_strchr(command, c)) / sizeof(char);
	pos = ft_get_pos(command, c);
	deleted = ft_substr(command, ft_get_pos(command, c) + 1, size - 1);
	ft_memmove(ft_strchr(command, c) - 1,
		ft_strrchr(command, c) + 1, size);
	deleted = ft_remove_slash(deleted);
	command_array = ft_special_split(command, ' ');
	command_array[(sizeof(command_array) / sizeof(char *))] = deleted;
	return (command_array);
}

char	**ft_get_command_arg_array(char *command)
{
	char			**command_array;

	if (ft_strchr_count(command, '\'') == 2)
	{
		command_array = ft_delete_char_and_split(command, '\'');
		return (command_array);
	}
	if (ft_strchr_count(command, '"') == 2)
	{
		command_array = ft_delete_char_and_split(command, '"');
		return (command_array);
	}
	command_array = ft_split(command, ' ');
	return (command_array);
}

// int	main(int argc, char **argv)
// {
// 	int		i;
// 	char	**command_array;

// 	command_array = ft_get_command_arg_array(argv[1]);
// 	i = 0;
// 	printf("string command: %s\n", command_array[i]);
// 	while (command_array[i])
// 	{
// 		printf("string command: %s\n", command_array[++i]);
// 	}
// }
