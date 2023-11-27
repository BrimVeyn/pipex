/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:33:32 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/27 19:04:00 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	pipex_exec(char	**cmds, char **env, t_pipex_data pdata)
{
	if (execve(cmds[0], cmds, env) == -1)
	{
		perror("Invalid command execution");
		free_cmds(pdata.cmds);
		return (-1);
	}
	return (0);
}

int	pipex_redirect(char	**cmds, char **env, int fdin, t_pipex_data pdata)
{
	pid_t	pid;
	int	pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid)
	{	
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
		close(pipe_fd[0]);

	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (fdin == STDIN_FILENO)
			exit(EXIT_FAILURE);
		else
		{
			if (pipex_exec(cmds, env, pdata) == -1)
				return (-1);
		}
		close(pipe_fd[1]);
	}
	return (0);
}

int	ft_strstr(char *haystack, char *needle)
{
	size_t	j;
	size_t	i;
	size_t const n_size = ft_strlen(needle);

	i = 0;
	while (haystack[i] != 0)
	{
		j = 0;
		if (haystack[i] == needle[j])
			while(haystack[++i] == needle[++j])
				if (j + 1 == n_size)
					return(i);
		i = i - j + 1;
	}
	return (0);
}

char	*ft_cdel(char *to_del, char *str)
{
	int	i;
	int	new_size;
	char	*new;

	i = -1;
	new_size = (int) (ft_strlen(str) - ft_strlen(to_del));
	if (!new_size)
	{
		free(str);
		return (NULL);
	}
	new = (char *) ft_calloc(new_size + 1, sizeof(char));
	while (++i < new_size - 1)
		new[i] = str[i];
	free(str);
	return (new);

}

void	read_till_delimiter(t_pipex_data pdata)
{
	char *buf;
	char *new;
	char *ndelimiter;
	int	bytes_read;

	bytes_read = 0;
	buf = ft_calloc(BUFFER_SIZE, 1);
	new = ft_calloc(1, 1);
	ndelimiter = ft_cjoin(ft_cjoin(strdup(pdata.delimiter), 10, 1, 0), 10, 1, 1);
	write(1, "heredoc> ", 9);
	while (ft_strstr(new, ndelimiter) == 0 && !(ft_strstr(new, pdata.delimiter) != 0 && ft_strlen(new) - 1 == ft_strlen(pdata.delimiter)))
	{
		bytes_read = read(STDIN_FILENO, buf, BUFFER_SIZE);
		new = ft_strjoinfree(new, buf);
		buf = ft_calloc(bytes_read, 1);
		if (new[ft_strlen(new) - 1] == '\n' && new[ft_strlen(new) - 2] != pdata.delimiter[ft_strlen(pdata.delimiter) - 1])
			write(1, "heredoc> ", 9);
	}
	new = ft_cdel(pdata.delimiter, new);
	write(pdata.fone_fd, new, ft_strlen(new));
	free(buf);
	free(ndelimiter);
	free(new);
}

int	pipex_open(char	*path, char *mode, t_pipex_data pdata)
{
	int	fd;

	if (ft_vstrcmp(mode, "read"))
		fd = open(path, O_RDONLY);
	else if (ft_vstrcmp(mode, "write"))
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 400);
	else if (ft_vstrcmp(mode, "append"))
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else
		fd = -1;
	if (fd == -1)
		pipex_error(FOPENING_FILE, pdata);
	return (fd);
}

void	pipex_check(int ac)
{
	if (ac < 5)
	{
		write(STDERR_FILENO, "Invalid number of arguments : pipex uses at least 4 arguments.\n", 63);
		exit(EXIT_FAILURE);
	}
}

void	pipex_fonecheck(t_pipex_data *pdata, char *av[], int ac)
{
	if (ft_vstrcmp("here_doc", av[1]))
	{
		pdata->delimiter = av[2];
		pdata->fone_path = ".heredoc_tmp";
		pdata->fone_fd = pipex_open(".heredoc_tmp", "write", *pdata);
		read_till_delimiter(*pdata);
		close(pdata->fone_fd);
		pdata->fone_fd = pipex_open(".heredoc_tmp", "read", *pdata);
		pdata->ftwo_fd = pipex_open(av[ac - 1], "append", *pdata);
	}
	else
	{
		pdata->fone_path = av[1];
		pdata->fone_fd = pipex_open(pdata->fone_path, "read", *pdata); 
		check_fone_access(pdata->fone_path);
		pdata->ftwo_fd = pipex_open(av[ac - 1], "write", *pdata);
	}
	pdata->ftwo_path = av[ac - 1];
}

int main (int ac, char	*av[], char *env[])
{
	t_pipex_data	pdata;
	int	c;

	pipex_check(ac);
	pipex_fonecheck(&pdata, av, ac);
	pdata.hd_offset = 1 * ft_vstrcmp("here_doc", av[1]);
	pdata.cmds_count = get_command_count(av, pdata.hd_offset);
	pdata.cmds = get_command_list(av, pdata.cmds_count, pdata.hd_offset);
	dup2(pdata.fone_fd, STDIN_FILENO);
	dup2(pdata.ftwo_fd, STDOUT_FILENO);
	if (pipex_redirect(pdata.cmds[0], env, pdata.fone_fd, pdata) == -1)
		pipex_error("Error", pdata);
	c = 0;
	while (c < pdata.cmds_count - 1)
	{
		if (pipex_redirect(pdata.cmds[c++], env, pdata.fone_fd, pdata) == -1)
		{
			close(pdata.fone_fd);
			unlink(av[ac - 1]);
			free_cmds(pdata.cmds);
			exit(EXIT_FAILURE);
		}
	}
	if (pipex_exec(pdata.cmds[pdata.cmds_count - 1], env, pdata) == -1)
	{
		close(pdata.fone_fd);
		unlink(av[ac - 1]);
		free_cmds(pdata.cmds);
		exit(EXIT_FAILURE);
	}
	close(pdata.fone_fd);
	close(pdata.ftwo_fd);
	free_cmds(pdata.cmds);
	exit(EXIT_SUCCESS);
}
