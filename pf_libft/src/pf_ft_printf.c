/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ft_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:12:53 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/27 18:33:23 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pf_ft_printf.h"

static t_var_utils	initialize_var(void)
{
	t_var_utils	var;

	var.i = 0;
	var.len = 0;
	var.flag = 0;
	return (var);
}

t_var_utils	run_woflags(t_var_utils var, const char *fmt, va_list *args)
{
	if (var.flag_num == 0)
	{
		var.fstr = parse_format(&fmt[var.i], args, &var.alist);
		var.len += ft_strlen(var.fstr);
		if (var.fstr[0] != -45)
		{
			ft_putstr_fd(var.fstr, 2);
			free(var.fstr);
		}
		else
			execute_and_print_c(var.fstr, var.alist);
	}
	return (var);
}

t_var_utils	run_wflags(t_var_utils var, const char *fmt, va_list *args)
{
	var.alist = parse_flags(&fmt[var.i], var.flag_num, var.alist);
	var.i += var.flag_num;
	var.fstr = parse_format(&fmt[var.i], args, &var.alist);
	var.flag = (-1 * (var.fstr[0] == -45)) * (-1 * (var.flag == 0));
	if (var.flag == 1)
		var.len += execute_and_print_c(var.fstr, var.alist);
	if (var.flag == 0)
	{
		var.fstr = execute_flag(var.fstr, var.alist);
		ft_putstr_fd(var.fstr, 2);
		var.len += ft_strlen(var.fstr);
		free(var.fstr);
	}
	return (var);
}

int	ft_printf(const char *fmt, ...)
{
	va_list		args;
	t_var_utils	var;

	if (!fmt)
		return (-1);
	va_start(args, fmt);
	var = initialize_var();
	while (fmt[var.i])
	{
		if (fmt[var.i] == '%')
		{
			var.flag_num = flag_count(&fmt[++var.i]);
			var.alist = initialise_triglist(var.alist);
			if (var.flag_num == 0)
				var = run_woflags(var, fmt, &args);
			else
				var = run_wflags(var, fmt, &args);
		}
		else
			var.len += ft_putchar_fdm(fmt[var.i], 1);
		var.i++;
	}
	va_end(args);
	return (var.len);
}
