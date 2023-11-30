/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:30:13 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/30 13:25:22 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strstr(char *haystack, char *needle)
{
	size_t const	n_size = ft_strlen(needle);
	size_t			j;
	size_t			i;

	i = 0;
	while (haystack[i] != 0)
	{
		j = 0;
		if (haystack[i] == needle[j])
			while (haystack[++i] == needle[++j])
				if (j + 1 == n_size)
					return (i);
		i = i - j + 1;
	}
	return (0);
}

char	*ft_cdel(char *to_del, char *str)
{
	int		i;
	int		j;
	int		start;
	int		end;
	char	*new;

	i = -1;
	j = 0;
	start = ft_strstr(str, to_del) - (ft_strlen(to_del) - 1);
	end = ft_strstr(str, to_del);
	if (!(ft_strlen(str) - ft_strlen(to_del)))
	{
		free(str);
		return (NULL);
	}
	new = (char *)ft_calloc((ft_strlen(str) - ft_strlen(to_del)) + 1,
			sizeof(char));
	while (++i < (int)ft_strlen(str))
		if (!(i >= start && i <= end))
			new[j++] = str[i];
	free(str);
	return (new);
}
