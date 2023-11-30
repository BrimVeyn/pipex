/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:25:56 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/30 13:33:36 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	here_doc_freer(char *buf, char *ndelimiter, char *new)
{
	free(buf);
	free(ndelimiter);
	free(new);
}

void	read_till_delimiter(t_pipex_data *pdata)
{
	char	*buf;
	char	*new;
	char	*ndelimiter;
	int		bytes_read;

	bytes_read = 0;
	buf = ft_calloc(BUFFER_SIZE, 1);
	new = ft_calloc(1, 1);
	ndelimiter = ft_cjoin(ft_cjoin(strdup(pdata->delimiter), 10, 1, 0), 10, 1,
			1);
	write(1, "heredoc> ", 9);
	while (ft_strstr(new, ndelimiter) == 0 && !(ft_strstr(new,
				pdata->delimiter) != 0 && ft_strlen(new)
			- 1 == ft_strlen(pdata->delimiter)))
	{
		bytes_read = read(STDIN_FILENO, buf, BUFFER_SIZE);
		new = ft_strjoinfree(new, buf);
		buf = ft_calloc(bytes_read + BUFFER_SIZE, 1);
		if (new[ft_strlen(new) - 1] == '\n' && new[ft_strlen(new) - 2]
			!= pdata->delimiter[ft_strlen(pdata->delimiter) - 1])
			write(1, "heredoc> ", 9);
	}
	new = ft_cdel(pdata->delimiter, new);
	write(pdata->fone_fd, new, ft_strlen(new));
	here_doc_freer(buf, ndelimiter, new);
}
