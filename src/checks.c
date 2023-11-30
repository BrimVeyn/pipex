/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:34:23 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/30 14:22:20 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	pipex_open(char *path, char *mode, t_pipex_data *pdata)
{
	int	fd;

	fd = -1;
	if (ft_vstrcmp(mode, "read"))
		fd = open(path, O_RDONLY);
	else if (ft_vstrcmp(mode, "write"))
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 400);
	else if (ft_vstrcmp(mode, "append"))
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd == -1)
		pipex_open_error(FOPENING_FILE, pdata);
	return (fd);
}

void	pipex_check(int ac)
{
	if (ac < 5)
	{
		write(STDERR_FILENO,
			"Invalid number of arguments : pipex uses at least 4 arguments.\n",
			63);
		exit(EXIT_FAILURE);
	}
}

void	pipex_fonecheck(t_pipex_data *pdata, char *av[], int ac)
{
	if (ft_vstrcmp("here_doc", av[1]))
	{
		pdata->delimiter = av[2];
		pdata->fone_path = ".heredoc_tmp";
		pdata->fone_fd = pipex_open(".heredoc_tmp", "write", pdata);
		read_till_delimiter(pdata);
		close(pdata->fone_fd);
		pdata->fone_fd = pipex_open(".heredoc_tmp", "read", pdata);
		pdata->ftwo_fd = pipex_open(av[ac - 1], "append", pdata);
	}
	else
	{
		pdata->fone_path = av[1];
		pdata->fone_fd = pipex_open(pdata->fone_path, "read", pdata);
		pdata->ftwo_fd = pipex_open(av[ac - 1], "write", pdata);
	}
	pdata->ftwo_path = av[ac - 1];
}
