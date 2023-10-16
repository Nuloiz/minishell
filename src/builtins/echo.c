/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:29:06 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/16 12:46:43 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if there is -n after echo
// and return the position to start the echo string
static int	ft_check_newline(char **splitted, int *new_line)
{
	int	i;

	i = 1;
	if (splitted[i])
	{
		if (!(ft_strncmp("-n", splitted[i], 3)))
		{
			*new_line = 0;
			i++;
		}
	}
	return (i);
}

// prints args (maybe needed to be splitted with
// ft_split) and if first is -n then no newline at end
int	ft_echo(char *args)
{
	int		new_line;
	int		i;
	int		size;
	char	**splitted;

	splitted = ft_split(args, ' ');
	if (!splitted || !*splitted)
		return (0);
	size = ft_array_size(splitted);
	new_line = 1;
	i = ft_check_newline(splitted, &new_line);
	while (splitted[i])
	{
		ft_printf("%s", splitted[i]);
		if (i < size - 1)
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	ft_free_array(splitted);
	return (0);
}

// int	main(void)
// {
// 	char **echo;
// 	echo = ft_split("     -n      hello  my friend", ' ');
// 	ft_echo(echo);
// }
