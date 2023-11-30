/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:21:49 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/30 14:41:19 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void	pipex_path_error(char *message, t_pipex_data *pdata)
{
	ft_printf("Error No : %d\n%s: %s\n", errno, message, strerror(errno));
	free_env(pdata->env);
	free_cmds(pdata->cmds);
	close(pdata->fone_fd);
	close(pdata->ftwo_fd);
	unlink(pdata->ftwo_path);
	free(pdata->pidarr);
	free(pdata);
	exit(EXIT_FAILURE);
}

void	pipex_open_error(char *message, t_pipex_data *pdata)
{
	ft_printf("Error No : %d\n%s: %s\n", errno, message, strerror(errno));
	free(pdata);
	exit(EXIT_FAILURE);
}

void	pipex_empty_cmd_error(char *message, t_pipex_data *pdata)
{
	ft_printf("%s\n", message);
	free_cmds(pdata->cmds);
	free_env(pdata->env);
	free(pdata);
	exit(EXIT_FAILURE);
}

void	pipex_no_path_error(char *message, t_pipex_data *pdata)
{
	ft_printf("%s\n", message);
	free_cmds(pdata->cmds);
	free(pdata);
}
