/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:19:59 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/23 17:24:02 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
# define OFFSET 3

int	get_command_count(char	*av[])
{
	size_t	j;

	j = 0;
	while (av[j] != NULL)
	{
		j++;
	}
	return (j - OFFSET);
}
