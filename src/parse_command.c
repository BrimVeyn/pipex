/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:19:59 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/28 19:00:15 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>

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

char	*parse_env(char *exec, t_pipex_data pdata)
{
	char	*path;
	char	*realexec;
	size_t	i;

	i = 0;
	path = pipex_strstr(pdata.env, "PATH=");
	// ft_printf("\n%s", path);
	path = ft_cdel("PATH=", ft_strdup(path)); 
	// ft_printf("\n%s", path);
	pdata.env = ft_split(path, ':');
	while (pdata.env[i])
	{
		realexec = ft_strdup(exec);
		realexec = ft_cjoin(realexec, '/', 1, 0);
		realexec = ft_mstrjoin(realexec, pdata.env[i], 1, 0);
		// ft_printf("%s\n", realexec);
		if (access(realexec, X_OK) == 0)
			return (realexec);
		i++;
	}
	pipex_error("Path error: command not found.", pdata);
	return(path);
}

void	parse_cmds(char ***cmds, t_pipex_data pdata)
{
	size_t	i;

	i = 0;
	while(cmds[i] != NULL)
	{	
		// cmds[i][0] = ft_mstrjoin(cmds[i][0], "/usr/bin/", 1, 0);
		// (void) pdata;
		cmds[i][0] = parse_env(cmds[i][0], pdata);
		i++;
	}
}

char	***get_command_list(char *av[], t_pipex_data pdata) 
{
	char	***cmds;
	int	start = 2 + pdata.hd_offset;
	int end = pdata.cmds_count + 1 + pdata.hd_offset;
	int i;
	cmds = (char ***) ft_calloc(pdata.cmds_count + 1, sizeof(char **));
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
	parse_cmds(cmds, pdata);
	return (cmds);
}
