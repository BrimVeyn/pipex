/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:59:41 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/29 12:21:07 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_cmds(char ***cmds)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!cmds)
		return ;
	while (cmds[i] != NULL)
	{
		j = 0;
		while(cmds[i][j] != NULL)
		{
			free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}
