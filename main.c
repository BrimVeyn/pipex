/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:33:32 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/23 17:24:42 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main (int ac, char	*av[])
{
	if (ac != 5)
		return (0);
	char *fone_path = parse_file_one(av);
	char *ftwo_path = parse_file_two(av);
	int	command_count = get_command_count(av);
	ft_printf("Command count = %d\n", command_count);
	if (access(fone_path, F_OK | R_OK) == -1)
	{
		perror("Could not access file");
		exit(EXIT_FAILURE);
	}
	ft_printf("%s %s\n", fone_path, ftwo_path);

	// check_file_access(file1);
	// initialize_subprocesses(av);
	char *cmd1[] = {"/usr/bin/grep", "h", "test1", NULL};
	char *cmd2[] = {"/usr/bin/wc", "-l", NULL};
	int yesornot = access("test", F_OK | R_OK);
	int	fd_file1 = open("test1", O_RDONLY); //protection
	int fd_file2 = open("test2", O_CREAT | O_WRONLY, S_IRWXU); //protection
	int	fd_pipe[2];
	int	sub_pid;
	char	*buf = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	if (pipe(fd_pipe) == -1)
	{
		exit(EXIT_FAILURE);
	}
	sub_pid = fork();

	if (sub_pid == 0)
	{
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		{
			perror("Could not duplicate the pipe's in");
			exit(EXIT_FAILURE);
		}
		if (close(fd_pipe[0]) == -1 || close(fd_pipe[1]) == -1)
		{
			perror("Could not close the pipe");
			exit(EXIT_FAILURE);
		}
		if (execve(cmd1[0], cmd1, NULL) == -1)
		{
			// printf("Could not execute the %dth command\nError code : %d\nError message%s", 1, errno, strerror(errno));
			perror("Could not execute the first command");
			exit(EXIT_FAILURE);
		}
	}

	else if (sub_pid != 0)
	{
		if (dup2(fd_pipe[0], STDIN_FILENO) == - 1)
		{
			perror("Could not duplicate the pipe's out");
			exit(EXIT_FAILURE);
		}
		if (close(fd_pipe[0]) == -1 || close(fd_pipe[1]) == -1)
		{
			perror("Could not close the pipe");
			exit(EXIT_FAILURE);
		}
		if (execve(cmd2[0], cmd2, NULL) == -1)
		{
			perror("Could not execute the second command");
			exit(EXIT_FAILURE);
		}
	}

	waitpid(sub_pid, NULL, 0);
	close(fd_file1);
	close(fd_file2);
	free(fone_path);
	free(ftwo_path);
	free(buf);
}
