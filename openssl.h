/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:42:41 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/25 12:37:39 by efriedma         ###   ########.fr       */
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
# include "macros.h"
/*
 *this is for storing values associated with the md5 and sha256 algorithm
 */

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
}						t_hash;

/*
 *this is for function pointers and storing the name of the program for dispatch table use
 */

typedef	struct			s_type
{
	char				*name;
	void				*ptr;
}						t_type;

//options for output, string, no intro to the hash output, etc...

typedef struct			s_opt
{
	int					on;
	int					p;
	int					q;
	int					r;
	int					s;
}						t_opt;

//this is for creating hashing values

typedef struct			s_val
{
	unsigned int		a0;
	unsigned int		b0;
	unsigned int		c0;
	unsigned int		d0;
}						t_val;

//this is for creating hashing values

typedef struct			s_iter
{
	unsigned int		A;
	unsigned int		B;
	unsigned int		C;
	unsigned int		D;
	unsigned int		F;
	unsigned int		i;
	unsigned int		g;
	unsigned int		d;
}						t_iter;

//sha hashing struct

typedef struct			s_sha
{
	unsigned int		h0;
	unsigned int		h1;
	unsigned int		h2;
	unsigned int		h3;
	unsigned int		h4;
	unsigned int		h5;
	unsigned int		h6;
	unsigned int		h7;
}						t_sha;

int						rstdin(t_hash *h);
int						get_opt(int argc, char **argv, t_opt *new, int i);
void					md5hash(char *str);
void					sha256hash(t_hash *hs, t_opt *nopt);
void					hash(t_hash *h, t_opt *new);
void					sha256start(char **argv, int argc);
void					md5start(char **argv, int argc);
void					sha256(char	**argv, int argc);
void					epad(t_hash *h);
int						rkey(t_hash *h);
int						ft_fread(char *str, t_hash *h);

#endif
