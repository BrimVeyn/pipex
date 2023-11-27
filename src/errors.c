/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:21:49 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/27 18:41:57 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex_error(char *message, t_pipex_data pdata)
{
	ft_printf("%s %s", message, pdata.fone_path);
	close(pdata.fd_fone);
	close(pdata.fd_ftwo);
	unlink(pdata.ftwo_path);
	exit(EXIT_FAILURE);
}
