/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_triglist_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 07:50:07 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:40:12 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pf_ft_printf.h"

t_flag_triglist	initialise_triglist(t_flag_triglist triglist)
{
	triglist.dash = 0;
	triglist.zero = 0;
	triglist.dot = 0;
	triglist.hash = 0;
	triglist.blank = 0;
	triglist.plus = 0;
	triglist.num_one = 0;
	triglist.num_two = 0;
	triglist.type = '0';
	return (triglist);
}

static int	ft_fp(char c)
{
	if (c == '0' || c == '#' || c == '+')
		return (1);
	else if (c == '-' || c == '.' || c == ' ')
		return (0);
	return (-1);
}

static t_flag_triglist	parse_flags_helper_one(const char *fmt, size_t numsize,
		size_t *i, t_flag_triglist triglist)
{
	if (fmt[*i] == '#')
		triglist.hash = 1;
	if (fmt[*i] == '0')
	{
		triglist.zero = 1;
		triglist.num_one = ft_parse_num(&fmt[++(*i)], &numsize);
		*i += numsize;
	}
	if (fmt[*i] == '+')
	{
		triglist.plus = 1;
		if (fmt[*i + 1] != '0')
			triglist.num_one = ft_parse_num(&fmt[++(*i)], &numsize);
		*i += numsize;
	}
	return (triglist);
}

static t_flag_triglist	parse_flags_helper_two(const char *fmt, size_t numsize,
		size_t *i, t_flag_triglist triglist)
{
	if (fmt[*i] == '-')
	{
		triglist.dash = 1;
		triglist.num_one = ft_parse_num(&fmt[++(*i)], &numsize);
		*i += numsize;
	}
	if (fmt[*i] == '.')
	{
		triglist.dot = 1;
		triglist.num_two = ft_parse_num(&fmt[++(*i)], &numsize);
		*i += numsize - 1;
	}
	if (fmt[*i] == ' ')
		triglist.blank = 1;
	return (triglist);
}

t_flag_triglist	parse_flags(const char *fmt, size_t flag_num,
		t_flag_triglist triglist)
{
	size_t	i;
	size_t	numsize;

	i = 0;
	numsize = 0;
	while (i < flag_num)
	{
		if (fmt[i] != '0')
			triglist.num_one = ft_parse_num(&fmt[i], &numsize);
		i += numsize;
		if (ft_fp(fmt[i]) == 1)
			triglist = parse_flags_helper_one(fmt, numsize, &i, triglist);
		if (ft_fp(fmt[i]) == 0)
			triglist = parse_flags_helper_two(fmt, numsize, &i, triglist);
		i++;
	}
	return (triglist);
}
