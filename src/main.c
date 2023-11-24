/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:33:32 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/24 17:28:10 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdlib.h>
#include <unistd.h>

int	pipex_exec(char **cmds, char **env)
{
	if (execve(cmds[0], cmds, env) == -1)
	{
		perror("Invalid command execution");
		return (-1);
	}
	return (0);
}

int	pipex_redirect(char **cmds, char **env, int fdin)
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
			if (pipex_exec(cmds, env) == -1)
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
					return(1);
		i = i - j + 1;
	}
	return (0);
}


char	*read_till_delimiter(char *delimiter)
{
	char *buf;
	int	bytes_read;

	bytes_read = 0;
	buf = ft_calloc(1, 1);
	while (ft_strstr(buf, delimiter) == 0)
	{
		read(0, buf, 1);
	}
	return (buf);
}

int main (int ac, char	*av[], char *env[])
{
	char	*fone_path;
	char	*delimiter;
	int		fd_file1;

	if (ac < 5)
		write(STDERR_FILENO, "Invalid number of arguments\n", 28);
	if (ft_vstrcmp("here_doc", av[1]))
	{
		delimiter = av[2];
		char *stdin_read = read_till_delimiter(delimiter);
	}
	else
	{
		fd_file1 = open(av[1], O_RDONLY); 
		check_fone_access(fone_path);
	}
	
	int	cmds_count = get_command_count(av);
	char ***cmds = get_command_list(av, cmds_count);

	// size_t	i = 0;
	// size_t	j = 0;
	//
	// while (cmds[i] != NULL)
	// {
	// 	ft_printf("Command %zu\n", i + 1);
	// 	j = 0;
	// 	while (cmds[i][j] != NULL)
	// 	{
	// 		ft_printf("cmds[%zu][%zu] = %s\n", i, j, cmds[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }

	int fd_file2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU); 

	dup2(fd_file1, STDIN_FILENO);
	dup2(fd_file2, STDOUT_FILENO);
	
	if (pipex_redirect(cmds[0], env, fd_file1) == -1)
	{
		close(fd_file1);
		unlink(av[ac -1]);
		free_cmds(cmds);
		exit(EXIT_FAILURE);
	}
	int	c = 0;
	while (c < cmds_count - 1)
	{
		if (pipex_redirect(cmds[c++], env, STDOUT_FILENO) == -1)
		{
			close(fd_file1);
			unlink(av[ac - 1]);
			free_cmds(cmds);
			exit(EXIT_FAILURE);
		}
	}
	if (pipex_exec(cmds[cmds_count - 1], env) == -1)
	{
		close(fd_file1);
		unlink(av[ac - 1]);
		free_cmds(cmds);
		exit(EXIT_FAILURE);
	}
	close(fd_file1);
	close(fd_file2);
	free_cmds(cmds);
}
