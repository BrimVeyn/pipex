/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:27:07 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:40:12 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pf_ft_printf.h"

int	ft_putchar_fdm(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

char	*ft_strupp(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return (str);
}

int	is_in(const char *fmt, const char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (fmt[0] == charset[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	flag_count(const char *fmt)
{
	char const	*charset;
	size_t		i;

	charset = "cspdiuxX%";
	i = 0;
	while (!is_in(&fmt[i], charset))
		i++;
	return (i);
}
