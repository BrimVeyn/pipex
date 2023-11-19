/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:10:25 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:40:12 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pf_ft_printf.h"

int	ft_parse_num(const char *fmt, size_t *numsize)
{
	size_t	i;
	int		recep;

	i = 0;
	recep = 0;
	while (ft_isdigit(fmt[i]) == 1)
	{
		recep = recep * 10 + (fmt[i] - '0');
		i++;
	}
	*numsize = i;
	return (recep);
}
