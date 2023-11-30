/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:54:01 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/24 17:04:17 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_file_two(char *av[])
{
	size_t	j;

	j = 0;
	while (av[j] != NULL)
		j++;
	return (ft_strdup(av[j - 1]));
}
