/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:34:26 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/28 16:30:57 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define OFFSET 3
# define BUFFER_SIZE 10
# define FOPENING_FILE "Could not open file"

#include "../pf_libft/include/pf_ft_printf.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

typedef struct s_pipex_data
{
	char	***cmds;
	char	**env;
	char	*delimiter;
	char	*stdin_read;
	char	*fone_path;
	char	*ftwo_path;
	int		fone_fd;
	int		ftwo_fd;
	int		hd_offset;	
	int		cmds_count;

}	t_pipex_data;

int		get_command_count(char	*av[], int hd_offset);
int		check_fone_access(char	*fone_path);
int		ft_vstrcmp(char	*s1, char	*s2);
int	ft_strstr(char *haystack, char *needle);
char	***get_command_list(char *av[], t_pipex_data pdata);
char	*get_file_one(char	*av[]);
char	*get_file_two(char	*av[]);
char	*get_delimiter(char	*av[]);
char	*ft_mstrjoin(const char *fstr, char *a_str, int n, int p);
char	*pipex_strstr(char **haystack, char *needle);
char	*ft_cdel(char *to_del, char *str);
char	*parse_env(char *exec, t_pipex_data pdata);
void	pipex_error(char *message, t_pipex_data pdata);
void	parse_cmds(char ***cmds, t_pipex_data pdata);
void	free_cmds(char ***cmds);

#endif
