/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:29:06 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/02 18:48:45 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tools/ft_printf/ft_printf.h"
#include <unistd.h>
#include <limits.h>

int	ft_array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	ft_echo(char **args)
{
	int	new_line;
	int	i;
	int	size;

	size = ft_array_size(args);
	i = 0;
	new_line = 0;
	if (!(ft_strncmp("-n", args[i], 3)))
	{
		new_line = 1;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s",args[i]);
		if (i < size - 1)
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	return (0);
}

int main(void)
{
	char **echo;
	
	echo = ft_split("     -n      hello  my friend", ' ');
	ft_echo(echo);
}
