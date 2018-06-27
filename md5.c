/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:21:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/25 23:36:12 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

int file = 0;

int		shash(char *hash1, t_hash *h, t_opt *new)
{
//	ft_printf("segfault in shash: %s\n", hash1);
	if (new->p && hash1 && h->pipe)
		ft_printf("%s", h->data);
	if (!hash1)
		return (0);
	if (!h->pipe)
	{
		ft_printf("pipe was off\n");
		h->data = ft_strdup(hash1);	
	}	
	h->name = hash1;
	if (h->data)
		h->bytes = ft_strlen(h->data);
	h->ini = h->bytes;
	epad(h);
	h->arr = (unsigned int *)h->data;
	hash(h, new);
	ft_memdel((void**)&h->data);
	return (1);
}

int		fhash(char *hash1, t_hash *h, t_opt *new)
{
//	ft_printf("segfault in fhash\n");
	if (!ft_fread(hash1, h))
		return (0);
	h->name = hash1;
	epad(h);
	h->arr = (unsigned int *)h->data;
	hash(h, new);
	file = 1;
	ft_memdel((void**)&h->data);
	return (1);
}

void	zeroh(t_opt *h, t_hash *hash)
{
	hash->pipe = 0;
	h->on = 0;
	h->s = 0;
	h->p = 0;
	h->q = 0;
}

void	error(void)
{
	ft_printf("md5: option requires an argument -- s\n");
	ft_printf("usage: md5 [-pqrtx] [-s string] [files ...]\n");
	exit(0);
}

void	fstruct(t_opt *opt, t_hash *h)
{
	free(h);
	free(opt);
}

void	md5start(char **argv, int argc)
{
	t_hash	*h;
	t_opt	*s;
	size_t	i;

	i = 2;
	s = ft_memalloc(sizeof(t_opt));
	h = ft_memalloc(sizeof(t_hash));
	while (get_opt(argc, argv, s, i))
		i++;
	if ((int)i == argc && rstdin(h))
	{
		h->pipe = 1;
		shash(h->data, h, s);
	}
	if (s->p)
	{
		//ft_printf("s->p %d\n", s->p);
		rstdin(h);	
		shash(h->data, h, s);
		zeroh(s, h);
	}
	else if (!h->pipe && argc == (int)i && rkey(h))
	{
		s->q = 1;
		h->pipe = 1;
		shash(h->data, h, s);
		h->pipe = 0;
		zeroh(s, h);
	}
	while ((int)i < argc)
	{
		h->pipe = 0;
		while (get_opt(argc, argv, s, i) && (int)i < argc && !file)
			i++;
//		ft_printf("argv[%d]: %s\n", i, argv[i]);
		if (!file && s->on && s->s)
			shash(argv[i], h, s);
		else if (!fhash(argv[i], h, s))
			ft_printf("ft_ssl: md5: %s: No such file or directory\n", argv[i]);
		else if (!file && ((int)i == argc && rstdin(h)))
			shash(h->data, h, s);
		zeroh(s, h);
		i++;
	}
	//	if ((int)i == argc && rstdin(h))
	//		shash(h->data, h, s);
	fstruct(s, h);
}
