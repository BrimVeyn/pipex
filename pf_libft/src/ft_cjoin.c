/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 07:57:41 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:40:12 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pf_ft_printf.h"

char	*ft_cjoin(const char *fstr, int c, int n, int p)
{
	char	*tmp;
	char	*result;

	if (n < 0)
		return ((char *)fstr);
	tmp = (char *)malloc(sizeof(char) * n + 1);
	if (!tmp)
		return (NULL);
	tmp = ft_memset(tmp, c, n);
	tmp[n] = '\0';
	if (p == 0)
		result = ft_strjoin(tmp, fstr);
	if (p == 1)
		result = ft_strjoin(fstr, tmp);
	free(tmp);
	free((void *)fstr);
	return (result);
}
