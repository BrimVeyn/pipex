/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:34:26 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/23 17:24:30 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define OFFSET 3
# define BUFFER_SIZE 100

#include "pf_libft/include/pf_ft_printf.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

char	*parse_file_one(char	*av[]);
char	*parse_file_two(char	*av[]);
int	get_command_count(char	*av[]);

#endif
