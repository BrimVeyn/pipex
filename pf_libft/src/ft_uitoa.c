/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:28:34 by bvan-pae          #+#    #+#             */
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
		n /= 10;
	}
	return (size);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	size_t	size;

	size = calculate_size(n);
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[--size] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
