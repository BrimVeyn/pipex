/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:19:59 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/30 14:52:46 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	get_command_count(char *av[], int hd_offset)
{
	size_t	j;

	j = 0;
	while (av[j] != NULL)
	{
		j++;
	}
	return (j - OFFSET - hd_offset);
}

char	*parse_env(char *exec, t_pipex_data *pdata)
{
	char	*realexec;
	size_t	i;

	i = 0;
	while (pdata->env[i])
	{
		realexec = ft_strdup(exec);
		realexec = ft_cjoin(realexec, '/', 1, 0);
		realexec = ft_mstrjoin(realexec, pdata->env[i], 1, 0);
		if (access(realexec, X_OK) == 0)
		{
			free(exec);
			return (realexec);
		}
		else
			free(realexec);
		i++;
	}
	return (NULL);
}

char	*parse_cmds(char **cmds, t_pipex_data *pdata)
{
	char	*env;

	if (cmds[0] == NULL)
		pipex_empty_cmd_error(EMPTY_COMMAND, pdata);
	if (is_dotslash(cmds[0]))
		pipex_empty_cmd_error(INVALID_COMMAND, pdata);
	if (access(cmds[0], X_OK) == 0)
		return (cmds[0]);
	env = parse_env(cmds[0], pdata);
	if (env == NULL)
		pipex_path_error("Path error: command not found ", pdata);
	return (env);
}

void	get_command_list(char *av[], t_pipex_data *pdata)
{
	int		start;
	int		end;
	int		i;
	char	*path;

	start = 2 + pdata->hd_offset;
	end = pdata->cmds_count + 1 + pdata->hd_offset;
	pdata->cmds = (char ***)ft_calloc(pdata->cmds_count + 1, sizeof(char **));
	if (!pdata->cmds)
		return ;
	i = 0;
	path = pipex_strstr(pdata->env, "PATH=");
	if (!path)
		pipex_no_path_error(NO_PATH, pdata);
	path = ft_cdel("PATH=", ft_strdup(path));
	pdata->env = ft_split(path, ':');
	free(path);
	while (start <= end)
	{
		pdata->cmds[i] = ft_split(av[start], ' ');
		pdata->cmds[i][0] = parse_cmds(pdata->cmds[i], pdata);
		start++;
		i++;
	}
	pdata->cmds[i] = NULL;
}
