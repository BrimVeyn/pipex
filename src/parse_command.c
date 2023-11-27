/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:19:59 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/27 09:48:34 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	get_command_count(char	*av[], int hd_offset)
{
	size_t	j;

	j = 0;
	while (av[j] != NULL)
	{
		j++;
	}
	return (j - OFFSET - hd_offset);
}

void	parse_cmds(char ***cmds)
{
	size_t	i;

	i = 0;
	while(cmds[i] != NULL)
	{
		cmds[i][0] = ft_mstrjoin(cmds[i][0], "/usr/bin/", 1, 0);
		i++;
	}
}

char	***get_command_list(char *av[], int command_count, int hd_offset)
{
	char	***cmds;
	int	start = 2 + hd_offset;
	int end = command_count + 1 + hd_offset;
	int i;
	cmds = (char ***) ft_calloc(command_count + 1, sizeof(char **));
	if (!cmds)
		return(NULL);
	i = 0;
	while (start <= end)
	{
		cmds[i] = ft_split(av[start], ' ');
		start++;
		i++;
	}
	cmds[i] = NULL;
	parse_cmds(cmds);
	return (cmds);
}
