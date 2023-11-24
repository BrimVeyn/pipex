/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:34:26 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/24 09:02:57 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define OFFSET 3
# define BUFFER_SIZE 100

#include "../pf_libft/include/pf_ft_printf.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

char	*get_file_one(char	*av[]);
char	*get_file_two(char	*av[]);
int	get_command_count(char	*av[]);
int	check_fone_access(char	*fone_path);
char	*ft_mstrjoin(const char *fstr, char *a_str, int n, int p);
int	ft_vstrcmp(char	*s1, char	*s2);
char	*get_delimiter(char	*av[]);
char	***get_command_list(char *av[], int command_count);
void	parse_cmds(char ***cmds);
void	free_cmds(char ***cmds);

#endif
