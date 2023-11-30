/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:34:26 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/30 15:20:26 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define OFFSET 3
# define BUFFER_SIZE 10
# define FOPENING_FILE "Could not open file"
# define EMPTY_COMMAND "Invalid command : Empty string"
# define NO_PATH "No path found in env variable"
# define INVALID_COMMAND "Invalid command : found dot(s) and slash(s) only"

# include "../pf_libft/include/pf_ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
	int		iterator;
	int		count;
	pid_t	*pidarr;

}			t_pipex_data;

int			get_command_count(char *av[], int hd_offset);
int			check_fone_access(char *fone_path);
int			ft_vstrcmp(char *s1, char *s2);
int			ft_strstr(char *haystack, char *needle);
int			pipex_open(char *path, char *mode, t_pipex_data *pdata);
int			is_dotslash(char *s);
void		get_command_list(char *av[], t_pipex_data *pdata);
char		*get_file_one(char *av[]);
char		*get_file_two(char *av[]);
char		*get_delimiter(char *av[]);
char		*ft_mstrjoin(const char *fstr, char *a_str, int n, int p);
char		*pipex_strstr(char **haystack, char *needle);
char		*ft_cdel(char *to_del, char *str);
char		*parse_env(char *exec, t_pipex_data *pdata);
char		*parse_cmds(char **cmds, t_pipex_data *pdata);
void		pipex_path_error(char *message);
void		pipex_open_error(char *message, t_pipex_data *pdata);
void		pipex_empty_cmd_error(char *message, t_pipex_data *pdata);
void		pipex_no_path_error(char *message, t_pipex_data *pdata);
void		free_cmds(char ***cmds);
void		free_env(char **env);
void		free_and_exit(t_pipex_data *pdata);
void		read_till_delimiter(t_pipex_data *pdata);
void		pipex_check(int ac);
void		pipex_fonecheck(t_pipex_data *pdata, char *av[], int ac);

#endif
