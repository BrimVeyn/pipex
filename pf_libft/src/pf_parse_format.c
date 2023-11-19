/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 08:19:52 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:40:12 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pf_ft_printf.h"

void	set_type(t_flag_triglist *trig, char c)
{
	trig->type = c;
}

char	*parse_format(const char *fmt, va_list *args, t_flag_triglist *triglist)
{
	if (set_type(triglist, 'd'), *fmt == 'd' || *fmt == 'i')
		return (ft_dupnfree(ft_itoa(va_arg(*args, int))));
	else if (set_type(triglist, 's'), *fmt == 's')
		return (ft_strdupm(va_arg(*args, char *)));
	else if (set_type(triglist, 'c'), *fmt == 'c')
		return (ft_strdupchar((char)va_arg(*args, int)));
	else if (set_type(triglist, 'u'), *fmt == 'u')
		return (ft_dupnfree(ft_uitoa(va_arg(*args, unsigned int))));
	else if (set_type(triglist, 'x'), *fmt == 'x')
		return (ft_dupnfree(ft_uitoahex(va_arg(*args, unsigned int))));
	else if (set_type(triglist, 'X'), *fmt == 'X')
		return (ft_dupnfree(ft_strupp(ft_uitoahex(va_arg(*args,
							unsigned int)))));
	else if (*fmt == '%')
		return (ft_strdup("%"));
	else if (set_type(triglist, 'p'), *fmt == 'p')
		return (ft_llitoahex(va_arg(*args, unsigned long long int)));
	return (ft_strdup(""));
}
