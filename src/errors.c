/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:21:49 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/27 19:04:54 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex_error(char *message, t_pipex_data pdata)
{
	ft_printf("%s %s", message, pdata.fone_path);
	close(pdata.fone_fd);
	close(pdata.ftwo_fd);
	unlink(pdata.ftwo_path);
	exit(EXIT_FAILURE);
}
