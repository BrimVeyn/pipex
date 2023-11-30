/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:33:32 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/30 14:58:50 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	pipex_redirect(char **cmds, char **env, t_pipex_data *pdata)
{
	int	pipe_fd[2];

	pipe(pipe_fd);
	pdata->pidarr[pdata->iterator] = fork();
	if (pdata->pidarr[pdata->iterator])
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	else if (!pdata->pidarr[pdata->iterator])
	{
		close(pdata->fone_fd);
		close(pipe_fd[0]);
		if (pdata->iterator != pdata->cmds_count)
			dup2(pipe_fd[1], STDOUT_FILENO);
		else
			dup2(pdata->ftwo_fd, STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pdata->ftwo_fd);
		execve(cmds[0], cmds, env);
	}
	pdata->iterator++;
	return (0);
}

int	main(int ac, char *av[], char *env[])
{
	t_pipex_data	*pdata;
	int				c;

	pipex_check(ac);
	pdata = (t_pipex_data *)malloc(1 * sizeof(t_pipex_data));
	pdata->iterator = 1;
	pdata->count = 1;
	pipex_fonecheck(pdata, av, ac);
	pdata->env = env;
	pdata->hd_offset = 1 * ft_vstrcmp("here_doc", av[1]);
	pdata->cmds_count = get_command_count(av, pdata->hd_offset);
	get_command_list(av, pdata);
	pdata->pidarr = (pid_t *)malloc(pdata->cmds_count * sizeof(pdata->pidarr));
	dup2(pdata->fone_fd, STDIN_FILENO);
	c = 0;
	while (c < pdata->cmds_count)
		pipex_redirect(pdata->cmds[c++], env, pdata);
	while (pdata->count <= pdata->cmds_count)
		waitpid(pdata->pidarr[pdata->count++], NULL, 0);
	free_and_exit(pdata);
}
