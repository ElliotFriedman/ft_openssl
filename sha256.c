/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 17:04:26 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/27 13:58:34 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

void    print_bytes(void *ptr, size_t size);

unsigned int	swap_endian(unsigned int num)
{
	unsigned int	b[4];
	//	unsigned int	j;

	//	ft_printf("%b %b %b %b\n", m[0], m[1], m[2], m[3]);
	b[0] = (num & 0x000000ff) << 24u;
	b[1] = (num & 0x0000ff00) << 8u;
	b[2] = (num & 0x00ff0000) >> 8u;
	b[3] = (num & 0xff000000) >> 24u;
	/*j =*/ return ( b[0] | b[1] | b[2] | b[3]);
	//	ft_printf("| %b %b %b %b\n", m[0], m[1], m[2], m[3]);
	//	return (j);
}

void	swap(t_hash *h)
{
	size_t	i;
	unsigned char   *m;

	m = 0;
	i = 0;
	print_bytes((void*)h->data, h->bytes);
	while (i <= ((h->bytes) / 4))
	{
		h->arr[i] = swap_endian(h->arr[i]);
		i++;
	}
	ft_printf("\ni after swap endian %d\n\n", i);
/*	
 *	while (i < h->bytes / 4)
 *	{
 *		m = (unsigned char*)&h->arr[i];
		ft_printf("%b %b %b %b\n", m[0], m[1], m[2], m[3]);
		i++;
	}
*/
	ft_printf("h->bytes: %d\n", h->bytes);
}

int		s256hash(char *hash1, t_hash *h, t_opt *s)
{
	if (!hash1)
	{
		ft_printf("Error!\n");
		exit(0);
	}
	h->data =  ft_strdup(hash1);
	h->name = hash1;
	h->bytes = ft_strlen(h->data);
	h->ini = h->bytes;
	epad(h);
	h->arr = (unsigned int *)h->data;
	swap(h);
	//epad(h);
	print_bytes((void*)h->data, h->bytes);
	sha256hash(h, s);
	ft_memdel((void**)&h->data);
	return (1);
}

int		f256hash(char *hash1, t_hash *h, t_opt *s)
{
	if (!ft_fread(hash1, h))
		return (0);
	h->name = hash1;
	printf("\n\n%s\n\n", h->name);
	epad(h);
	print_bytes((void*)h->data, h->bytes);
	h->arr = (unsigned int *)h->data;
	//swap endianness
	swap(h);
	print_bytes((void*)h->data, h->bytes);
	sha256hash(h, s);
	ft_memdel((void**)&h->data);
	return (1);
}

void	zero(t_opt *h)
{
	h->on = 0;
	h->s = 0;
	h->p = 0;
	h->q = 0;
	h->r = 0;
}

void	err(void)
{
	ft_printf("sha256: option requires an argument -- s\n");
	ft_printf("usage: sha256 [-pqrtx] [-s string] [files ...]\n");
	exit(0);
}

void	sha256start(char **argv, int argc)
{
	t_hash	*h;
	t_opt	*s;
	size_t	i;

	i = 2;
	s = ft_memalloc(sizeof(t_opt));
	h = ft_memalloc(sizeof(t_hash));
	get_opt(argc, argv, s, 2);
	while (get_opt(argc, argv, s, i) && (int)i < argc)
		i++;
	if (argc == 3 && s->on)
		err();
	while ((int)i < argc)
	{
		if (s->on && s->s)
			s256hash(argv[i], h, s);
		else if ((int)i < argc && !f256hash(argv[i], h, s))
		{
			ft_printf("md5: %s: No such file or directory\n", argv[i]);
			exit(0);
		}
		zero(s);
		i++;
	}
}
