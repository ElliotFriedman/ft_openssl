/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:42:41 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/07 17:08:26 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENSSL_H
#define OPENSSL_H
#include "ft_printf/includes/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

typedef struct	s_hash
{
	//name of file we opened
	char				*name;
	//fd boolean
	size_t				fd;
	//initial value of all data values read in
	unsigned long long	ini;
	//data we read in and are going to hash
	char				*data;
	//how many bytes we have to hash
	size_t				bytes;
	//how many arrays we have
	int					arrnum;
	//2d array of uints
	unsigned int		*arr;
}						t_hash;

typedef	struct			s_type
{
	char				*name;
	//function pointer
	void				*ptr;

}						t_type;


typedef struct			s_hash256
{
	char				*data;
}						t_hash256;

/*
typedef struct			s_flag
{
	int					on;
	int					p;
	int					q;
	int					r;
	int					s;
}						t_flag;
*/

typedef struct			s_opt
{
	int					on;
	int					p;
	int					q;
	int					r;
	int					s;
}						t_opt;

//could this array be unsigned
int						get_opt(int argc, char **argv, t_opt *new, int i);
void					md5hash(char *str);
void					hash(t_hash *h);
//void					options(int argc, char **argv, t_flag *flag);
void					md5start(char **argv, int argc);
void					sha256(char	**argv, int argc);
void					epad(t_hash *h);
int						ft_fread(char *str, t_hash *h);

#endif
