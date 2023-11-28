/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:21:49 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/28 08:06:44 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <errno.h>
#include <string.h>

void	pipex_error(char *message, t_pipex_data pdata)
{
	ft_printf("Error No : %d\n%s: %s", errno, message, strerror(errno));
	if (pdata.cmds != NULL)
		free_cmds(pdata.cmds);
	close(pdata.fone_fd);
	close(pdata.ftwo_fd);
	unlink(pdata.ftwo_path);
	exit(EXIT_FAILURE);
}
