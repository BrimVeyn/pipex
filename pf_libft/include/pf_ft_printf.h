/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:34:33 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/30 10:21:03 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_FT_PRINTF_H
# define PF_FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>

typedef struct s_flag_triglist
{
	int				dash;
	int				zero;
	int				dot;
	int				hash;
	int				blank;
	int				plus;
	int				num_one;
	int				num_two;
	char			type;

}					t_flag_triglist;

typedef struct s_var_utils
{
	size_t			i;
	size_t			flag_num;
	t_flag_triglist	alist;
	char			*fstr;
	int				len;
	int				flag;

}					t_var_utils;

int					ft_printf(const char *fmt, ...);
char				*ft_uitoa(unsigned int n);
char				*ft_uitoahex(unsigned int n);
char				*ft_strupp(char *str);
char				*ft_dupnfree(const char *src);
char				*ft_strdupchar(int c);
char				*ft_llitoahex(unsigned long long n);
char				*ft_strdupm(const char *src);
int					ft_parse_num(const char *fmt, size_t *numsize);
char				*ft_strjoinfree(char const *s1, char const *s2);
char				*ft_substrfree(char const *s, unsigned int start,
						size_t len);
t_flag_triglist		initialise_triglist(t_flag_triglist triglist);
t_flag_triglist		parse_flags(const char *fmt, size_t flag_num,
						t_flag_triglist triglist);
char				*execute_flag(const char *fstr, t_flag_triglist a);
char				*ft_cjoin(const char *fstr, int c, int n, int p);
int					execute_and_print_c(char *newstr, t_flag_triglist a);
char				*ft_cjoin(const char *fstr, int c, int n, int p);
int					is_in(const char *fmt, const char *charset);
size_t				flag_count(const char *fmt);
void				set_type(t_flag_triglist *trig, char c);
char				*parse_format(const char *fmt, va_list *args,
						t_flag_triglist *triglist);
int					ft_putchar_fdm(char c, int fd);

#endif
