/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:26:46 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/27 18:29:36 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_fone_access(char	*fone_path)
{
	if (access(fone_path, F_OK | R_OK) == -1)
	{
		perror("Could not access file");
		exit(EXIT_FAILURE);
	}
	return (0);
}
