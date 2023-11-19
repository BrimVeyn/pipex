/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoahex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:17:31 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:40:12 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pf_ft_printf.h"

static int	calculate_size(unsigned long long n)
{
	size_t	size;

	size = 0;
	while (n != 0)
	{
		size++;
		n /= 16;
	}
	return (size);
}

char	*ft_llitoahex(unsigned long long n)
{
	char		*str;
	char const	*base;
	size_t		size;
	char		*final;

	base = "0123456789abcdef";
	size = calculate_size(n);
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	if (n == 0)
	{
		free(str);
		return (ft_strdup("(nil)"));
	}
	while (n != 0)
	{
		str[--size] = base[n % 16];
		n = n / 16;
	}
	final = ft_strjoin("0x", str);
	free(str);
	return (final);
}
