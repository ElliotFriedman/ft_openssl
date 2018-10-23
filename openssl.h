/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:42:41 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/23 01:26:41 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENSSL_H
# define OPENSSL_H
# include "ft_printf/includes/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

# define RR(a, shift) ((a >> shift) | (a << (32 - shift)))

typedef struct			s_hash
{
	char				*name;
	size_t				fd;
	unsigned long long	ini;
	char				*data;
	size_t				bytes;
	unsigned int		*arr;
	unsigned int		end;
	unsigned int		pipe;
	unsigned int		sha;
	size_t				i;
}						t_hash;

typedef	struct			s_type
{
	char				*name;
	void				*ptr;
}						t_type;

typedef struct			s_opt
{
	int					on;
	int					p;
	int					q;
	int					r;
	int					s;
}						t_opt;

typedef struct			s_val
{
	unsigned int		a0;
	unsigned int		b0;
	unsigned int		c0;
	unsigned int		d0;
}						t_val;

typedef struct			s_iter
{
	unsigned int		aa;
	unsigned int		bb;
	unsigned int		cc;
	unsigned int		dd;
	unsigned int		ff;
	unsigned int		i;
	unsigned int		g;
	unsigned int		d;
}						t_iter;

typedef struct			s_sha
{
	unsigned int		a;
	unsigned int		b;
	unsigned int		c;
	unsigned int		d;
	unsigned int		e;
	unsigned int		f;
	unsigned int		g;
	unsigned int		h;
	unsigned int		temp1;
	unsigned int		temp2;
	unsigned int		s0;
	unsigned int		s1;
	unsigned int		ss1;
	unsigned int		ss0;
	unsigned int		maj;
	unsigned int		ch;
	unsigned int		h0[8];
}						t_sha;

int						rstdin(t_hash *h);
int						get_opt(int argc, char **argv, t_opt *n, int i);
void					md5hash(char *str);
void					sha256hash(t_hash *hs, t_opt *nopt);
void					hash(t_hash *h, t_opt *n);
void					sha256start(char **argv, int argc);
void					md5start(char **argv, int argc);
void					sha256(char	**argv, int argc);
void					epad(t_hash *h);
void					handle_out1(t_sha *s, t_hash *h, t_opt *n);
void					whiled(t_sha *n, size_t i, unsigned int *w);
void					t_sha_init(t_sha *n);
int						rkey(t_hash *h);
int						ft_fread(char *str, t_hash *h);
void					set_n_run(t_hash *h, t_opt *s);
int						one_two(int argc, t_opt *s, t_hash *h);
int						do_one(t_opt *s, t_hash *h, int *file);
size_t					get_opt_loop(size_t i, int argc, char **argv, t_opt *s);
void					zer0h(t_opt *h, t_hash *hash);
int						s256hash(char *hash1, t_hash *h, t_opt *s);
void					swap(t_hash *h);

#endif
