/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:41:17 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/09 08:41:42 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_exit(char **array)
{
	ft_free_array(array);
	exit(0);
}
