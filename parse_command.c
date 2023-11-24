/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:19:59 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/24 07:25:32 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_libft/include/libft.h"
#include "pipex.h"

int	get_command_count(char	*av[])
{
	size_t	j;

	j = 0;
	while (av[j] != NULL)
	{
		j++;
	}
	return (j - OFFSET);
}

char	*get_delimiter(char	*av[])
{
	return(ft_strdup(av[1]));
}


char	***get_command_list(char *av[], int command_count)
{
//* */	char *cmd1[] = {"/usr/bin/grep", "h", "test1", NULL};
	char	***cmds;
	int	start = 2;
	int end = command_count + 1;
	int i;
	cmds = (char ***) ft_calloc(command_count + 1, sizeof(char **));
	if (!cmds)
		return(NULL);
	i = 0;
	while (start <= end)
	{
		// ft_printf("%s", av[start]);
		cmds[i] = ft_split(av[start], ' ');
		// ft_printf("|%s|", cmds[i][0]);
		start++;
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}
