/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:31:03 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/30 14:54:55 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_mstrjoin(const char *fstr, char *a_str, int n, int p)
{
	char		*tmp;
	char		*result;
	int			i;
	int const	size = (int) ft_strlen(a_str);

	if (n < 0)
		return ((char *)fstr);
	tmp = (char *)ft_calloc((size * n) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = -1;
	while (++i < (n * size))
		tmp[i] = a_str[i % size];
	if (p == 0)
		result = ft_strjoin(tmp, fstr);
	if (p == 1)
		result = ft_strjoin(fstr, tmp);
	free(tmp);
	free((void *)fstr);
	return (result);
}

int	ft_vstrcmp(char *s1, char *s2)
{
	size_t	s_s1;
	size_t	s_s2;
	int		i;

	i = -1;
	s_s1 = ft_strlen(s1);
	s_s2 = ft_strlen(s2);
	if (s_s1 != s_s2)
		return (0);
	while (++i < (int)s_s1)
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

char	*pipex_strstr(char **haystack, char *needle)
{
	size_t const	n_size = ft_strlen(needle);
	size_t			j;
	size_t			i;
	size_t			k;

	k = 0;
	while (haystack[k])
	{
		i = 0;
		while (haystack[k][i])
		{
			j = 0;
			if (haystack[k][i] == needle[j] && haystack[k][i - 1] != '_')
				while (haystack[k][++i] == needle[++j])
					if (j + 1 == n_size)
						return (&haystack[k][i - j]);
			i = i - j + 1;
		}
		k++;
	}
	return (NULL);
}

int	is_dotslash(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] == '/' || s[i] == '.'))
			return (0);
		i++;
	}
	return (1);
}
