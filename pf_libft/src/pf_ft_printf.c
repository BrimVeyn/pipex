/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ft_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:12:53 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:40:12 by bvan-pae         ###   ########.fr       */
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
			ft_putstr_fd(var.fstr, 1);
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
		ft_putstr_fd(var.fstr, 1);
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
//
// #include <limits.h>
//
// int	main(void)
// {
// 	// ft_printf("C = %-1c %-2c %-3c |\n", '2', '1', 0);
// 	// printf("R = %-1c %-2c %-3c |\n", '2', '1', 0);
// 	int a = ft_printf("C = %-50c now you see|\n", '\0');
// 	int b = printf("R = %-50c now you see|\n", '\0');
// 	printf("R : %d C = %d V = %d\n", (a == b), a, b);
// 	int c = ft_printf("%-5c%-5c|\n", 0, 'b');
// 	int d = printf("%-5c%-5c|\n", 0, 'b');
// 	printf("R : %d C = %d V = %d\n", (c == d), c, d);
// 	int e = ft_printf("%-2c%-3c%-4c*|\n", 0, 'a', 0);
// 	int f = printf("%-2c%-3c%-4c*|\n", 0, 'a', 0);
// 	printf("R : %d C = %d V = %d\n", (e == f), e, f);
// 	int g = ft_printf(" %-1c %-2c %-3c |\n", '2', '1', 0);
// 	int h = printf(" %-1c %-2c %-3c |\n", '2', '1', 0);
// 	printf("R : %d C = %d V = %d\n", (g == h), g, h);
// 	int var.i = ft_printf(" %-1c %-2c %-3c |\n", '0', 0, '1');
// 	int j = printf(" %-1c %-2c %-3c |\n", '0', 0, '1');
// 	printf("R : %d C = %d V = %d\n", (var.i == j), var.i, j);
// 	int k = ft_printf("%-2c%-3c%-4c*|\n", 0, 'a', 0);
// 	int l = printf("%-2c%-3c%-4c*|\n", 0, 'a', 0);
// 	printf("R : %d C = %d V = %d\n", (k == l), k, l);
// 	// int m = ft_printf(" %-1c %-2c %-3c |\n", '0', 0, '1');
// 	// int n = printf(" %-1c %-2c %-3c |\n", '0', 0, '1');
// 	// printf("R : %d C = %d V = %d\n", (m == n), m, n);
// 	// int o = ft_printf("%.5s", (char *) 0);
// 	// int p = printf("%.5s", (char *) 0);
// 	// printf("R : %d C = %d V = %d\n", (o == p), o, p);
// 	// printf("%-10.d", 0);
// 	// ft_printf("%-10.d", 0);
// 	// ft_printf("%-2c|%-3c|%-4c|*\n", 0, 'a', 0);
// 	// printf("%-2c|%-3c|%-4c|*\n", 0, 'a', 0);
// 	// ft_printf("%-.X", 0);
// 	// ft_printf("%10c|\n", 0);
// 	// printf("%10c|\n", 0);
// 	// ft_printf("%50s", 0);
// 	// ft_printf("%s", 0);
// 	// printf(" %-15d |\n", -1);
// 	// ft_printf(" %-15d |\n", -1);
// 	// printf(" %01u |\n", 0);
// 	// ft_printf(" %01u |\n", 0);
// 	// printf("%30.6d\n", 12);
// 	// ft_printf("%30.6d\n", 12);
// 	// printf("%30.6s\n", "ceciestunestring");
// 	// ft_printf("%30.6s\n", "ceciestunestring");
// 	// printf("%-30.6s\n", "ceciestunestring");
// 	// ft_printf("%-30.6s\n", "ceciestunestring");
// 	// printf("%+030.6d|\n", 12);
// 	// ft_printf("%+030.6d|\n", 12);
// 	// printf("%+030d|\n", 12);
// 	// ft_printf("%+030d|\n", 12);
// 	// printf("%-30d|\n", 12);
// 	// ft_printf("%-30d|\n", 12);
// 	// printf("%30d|\n", 12);
// 	// ft_printf("%30d|\n", 12);
// 	// printf("%#10x|\n", 2566);
// 	// ft_printf("%#10x|\n", 2566);
// 	// printf("%#010x|\n", 2566);
// 	// ft_printf("%#010x|\n", 2566);
// 	// printf("%#-10x|\n", 2566);
// 	// ft_printf("%#-10x|\n", 2566);
// 	// printf("%#.10x|\n", 2566);
// 	// ft_printf("%#.10x|\n", 2566);
// 	// printf("%#20.10x|\n", 2566);
// 	// ft_printf("%#20.10x|\n", 2566);
// 	// printf("%#-20.10x|\n", 2566);
// 	// ft_printf("%#-20.10x|\n", 2566);
// 	// printf("%#x|\n", 10);
// 	// ft_printf("%#x|\n", 10);
// 	// printf("%-4x|\n", 9);
// 	// ft_printf("%-4x|\n", 9);
// 	//
// 	// printf("%#10X|\n", 2566);
// 	// ft_printf("%#10X|\n", 2566);
// 	// printf("%#010X|\n", 2566);
// 	// ft_printf("%#010X|\n", 2566);
// 	// printf("%#-10X|\n", 2566);
// 	// ft_printf("%#-10X|\n", 2566);
// 	// printf("%#.10X|\n", 2566);
// 	// ft_printf("%#.10X|\n", 2566);
// 	// printf("%#20.10X|\n", 2566);
// 	// ft_printf("%#20.10X|\n", 2566);
// 	// printf("%#-20.10X|\n", 2566);
// 	// ft_printf("%#-20.10X|\n", 2566);
// 	// printf("% d|\n", 2256);
// 	// ft_printf("% d|\n", 2256);
// 	// printf("% 10.10d|\n", 2256);
// 	// ft_printf("% 10.10d|\n", 2256);
// 	// printf("% -4d|\n", 20);
// 	// ft_printf("% -4d|\n", 20);
// 	// printf("% 4d|\n", 20);
// 	// ft_printf("% 4d|\n", 20);
// 	// printf(" %5d |\n", -1);
// 	// ft_printf(" %5d |\n", -1);
// 	// printf(" %#x |\n", 0);
// 	// ft_printf(" %#x |\n", 0);
// 	// printf("%011d\n", 1111111);
// 	// ft_printf("%011d\n", 1111111);
// 	// printf("%011d\n", -1111111);
// 	// ft_printf("%011d\n", -1111111);
// 	// printf("%.11d\n", -1111111);
// 	// ft_printf("%.11d\n", -1111111);
// 	// printf("%-9d %-10d %-11d %-12d %-13d %-14d %-15d", INT_MAX, INT_MIN,
		// LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
// 	// ft_printf("%-9d %-10d %-11d %-12d %-13d %-14d %-15d", INT_MAX, INT_MIN,
		// LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
//
//
// 	// printf("p %p\n", (void *) 43);
// 	// ft_printf("p %p\n", (void *) 43);
// 	// printf("%x\n", (unsigned int) 4294967295);
// 	// printf("%x", (unsigned int) 2147483647);
// 	// printf("%%c  = %c \n", 'c');
// 	// printf("%%s  = %s \n", "str");
// 	// printf("%%p  = %p \n", (void *) 1278);
// 	// printf("%%d  = %d \n", 1278);
// 	// printf("%%var.i  = %var.i \n", 1278);
// 	// printf("%%u  = %u \n", 1278);
// 	// printf("%%x  = %x \n", 1278);
// 	// printf("%%X  = %X \n", 1278);
// 	// printf("%%   = %% \n");
// 	// printf("%%#x = %#x \n", 1278);
// 	// printf("%%#X = %#X \n", 1278);
// 	// printf("%%-#10x  = %-#10x|\n", 546);
// 	// printf("%%x      = %x|\n", 546);
// 	//
// 	// printf("\n%%#68.x    = %#68.x|\n", 456);
// 	// printf("%%#68x     = %#68x|\n", 456); //Cas particulier
// 	// printf("%%#.68x    = %#.68x|\n", 456);
// 	// printf("%%#.68x    = %.68d|\n", 456);
// 	// printf("%%#-68x    = %#-68x|\n", 456);
// 	//
// 	//
// 	//
// 	// printf("%%#68x  = %#68x|\n", 456);
// 	// printf("%%#068x  = %#068x|\n", 456);
// 	// printf("%%.68x   = %.68x|\n", 456);
// 	// printf("%%#10x   = %#10x|\n", 546);
// 	// printf("%%#010x  = %#010x|\n", 546);
// }
