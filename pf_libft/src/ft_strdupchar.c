/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:34:06 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:40:12 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pf_ft_printf.h"

char	*ft_strdupchar(int c)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * 2);
	if (c == 0)
		s[0] = -45;
	else
		s[0] = c;
	s[1] = 0;
	return (s);
}
