/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flags_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 07:53:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/27 18:33:09 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pf_ft_printf.h"

static char	*exec_flag_part_four(char *newstr, t_flag_triglist a)
{
	if (a.plus && a.zero && a.dot == 0)
		newstr = ft_memset(newstr, '+', 1);
	if (a.plus && a.zero && a.dot)
		newstr = ft_cjoin(newstr, '+', 1, 0);
	if (a.plus && a.num_one == 0 && newstr[0] != '-')
		newstr = ft_strjoinfree("+", newstr);
	if (a.plus && a.num_one)
		newstr = ft_cjoin(newstr, ' ', a.num_one - ft_strlen(newstr), 0);
	else if (a.dash == 0 && a.num_one)
		newstr = ft_cjoin(newstr, ' ', a.num_one - ft_strlen(newstr), 0);
	if (a.blank && (a.zero || a.dot) && newstr[0] != '-' && a.type != 's')
		newstr = ft_cjoin(newstr, ' ', 1, 0);
	if (a.type == 'X')
		return (ft_strupp(newstr));
	return (newstr);
}

static char	*exec_flag_part_three(char *newstr, t_flag_triglist a)
{
	if (a.zero && a.dot == 1 && a.num_one != 0 && a.num_two == 0
		&& newstr[0] == '0')
		newstr = ft_cjoin(ft_memset(newstr, ' ', 1), ' ', a.num_one
				- ft_strlen(newstr), 0);
	else if (a.zero && a.num_two == 0 && newstr[0] != '-')
		newstr = ft_cjoin(newstr, '0', a.num_one - ft_strlen(newstr), 0);
	else if (a.zero && a.num_two == 0 && newstr[0] == '-')
		newstr = ft_memset(ft_cjoin(ft_memset(newstr, '0', 1), '0', a.num_one
					- ft_strlen(newstr), 0), '-', 1);
	if (a.hash && a.zero && (a.type == 'x' || a.type == 'X'))
		newstr = ft_memset(ft_memset(&newstr[0], '0', 1) + 1, 'x', 1);
	else if ((a.type == 'x' || a.type == 'X') && a.hash
		&& !(ft_strlen(newstr) == 1 && newstr[0] == '0'))
		newstr = ft_strjoinfree("0x", newstr);
	return (exec_flag_part_four(newstr, a));
}

static char	*exec_flag_part_two(char *newstr, t_flag_triglist a,
		const char *base_str, int const offset)
{
	if (a.dash && (a.zero || a.hash))
		newstr = ft_cjoin(newstr, ' ', a.num_one - ft_strlen(newstr) - offset,
				1);
	else if (a.dot && ((a.dash && base_str[0] == '0' && !a.num_two
				&& !a.num_one) || (a.num_two < 6 && base_str[0] == '('
				&& a.type == 's')))
	{
		free(newstr);
		newstr = ft_strdup("");
	}
	else if (a.dash)
		newstr = ft_memset(ft_cjoin(newstr, ' ', a.num_one - ft_strlen(newstr),
					1), ' ', (base_str[0] == '0' && a.dot
					&& a.num_one >= a.num_two));
	free((void *)base_str);
	return (exec_flag_part_three(newstr, a));
}

char	*execute_flag(const char *fstr, t_flag_triglist a)
{
	char		*newstr;
	int const	offset = 2 * (a.type == 'x' || a.type == 'X');
	int const	base_len = (int)ft_strlen(fstr);
	const char	*base_str = ft_strdup(fstr);

	newstr = (char *)fstr;
	if (a.dot && base_str[0] == '0' && !a.zero)
		ft_memset(newstr, 0, 1);
	if (a.blank && a.zero == 0 && a.dot == 0 && newstr[0] != '-'
		&& a.type != 's')
		newstr = ft_cjoin(newstr, ' ', 1, 0);
	if (a.type == 's' && a.dot)
		newstr = ft_substrfree(newstr, 0, a.num_two);
	else if (a.num_two && newstr[0] == '-')
		newstr = ft_cjoin(ft_cjoin(ft_memset(newstr, '0', (base_len
							- 1 < a.num_two)), '0', a.num_two - base_len, 0),
				'-', (base_len - 1 < a.num_two), 0);
	else if (a.num_two)
		newstr = ft_cjoin(newstr, '0', a.num_two - ft_strlen(newstr), 0);
	return (exec_flag_part_two(newstr, a, base_str, offset));
}

int	execute_and_print_c(char *newstr, t_flag_triglist a)
{
	size_t	i;

	i = 0;
	if (a.dash && a.num_one)
		newstr = ft_cjoin(newstr, ' ', a.num_one - 1, (newstr[0] == -45));
	else if (a.num_one && !a.dash)
		newstr = ft_cjoin(newstr, ' ', a.num_one - 1, (newstr[0] != -45));
	while (newstr[i] != 0)
	{
		if (newstr[i] != -45)
			write(1, &newstr[i], 2);
		else
			write(1, "\0", 2);
		i++;
	}
	free(newstr);
	return (i);
}
