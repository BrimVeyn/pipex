/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:59:41 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/30 12:31:23 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_cmds(char ***cmds)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!cmds)
		return ;
	while (cmds[i] != NULL)
	{
		j = 0;
		while (cmds[i][j] != NULL)
		{
			free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

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

void	free_and_exit(t_pipex_data *pdata)
{
	close(pdata->fone_fd);
	close(pdata->ftwo_fd);
	free_cmds(pdata->cmds);
	free_env(pdata->env);
	free(pdata->pidarr);
	free(pdata);
	exit(EXIT_SUCCESS);
}
