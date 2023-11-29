/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:21:49 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/29 15:35:58 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <errno.h>
#include <string.h>


void	free_env(char **env)
{
	size_t	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}


void	pipex_path_error(char *message, t_pipex_data *pdata)
{
	ft_printf("Error No : %d\n%s: %s\n", errno, message, strerror(errno));
	free_env(pdata->env);
	free_cmds(pdata->cmds);
	close(pdata->fone_fd);
	close(pdata->ftwo_fd);
	unlink(pdata->ftwo_path);
	free(pdata);
	exit(EXIT_FAILURE);
}

void	pipex_open_error(char *message, t_pipex_data *pdata)
{
	ft_printf("Error No : %d\n%s: %s\n", errno, message, strerror(errno));
	free(pdata);
	exit(EXIT_FAILURE);
}
