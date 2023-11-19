/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoahex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:11:15 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:40:12 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pf_ft_printf.h"

static int	calculate_size(unsigned int n)
{
	size_t	size;

	if (n == 0)
		size = 1;
	else
		size = 0;
	while (n != 0)
	{
		size++;
		n /= 16;
	}
	return (size);
}

char	*ft_uitoahex(unsigned int n)
{
	char		*str;
	char const	*base;
	size_t		size;

	base = "0123456789abcdef";
	size = calculate_size(n);
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[--size] = base[n % 16];
		n = n / 16;
	}
	return (str);
}
