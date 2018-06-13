/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:21:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/12 20:11:41 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

int		shash(char *hash1, t_hash *h, t_opt *new)
{
//	ft_printf("%s\n", hash1);
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
	hash(h, new);
	return (1);
}

int		fhash(char *hash1, t_hash *h, t_opt *new)
{
	if (!ft_fread(hash1, h))
		return (0);
	h->name = hash1;
	epad(h);
	h->arr = (unsigned int *)h->data;
	hash(h, new);
	return (1);
}

void	zeroh(t_opt *h)
{
	h->on = 0;
	h->s = 0;
	h->p = 0;
	h->q = 0;
	h->r = 0;
}

void	error(void)
{
	ft_printf("md5: option requires an argument -- s\n");
	ft_printf("usage: md5 [-pqrtx] [-s string] [files ...]\n");
	exit(0);
}

void	md5start(char **argv, int argc)
{
	t_hash	*h;
	t_opt	*s;
	size_t	i;

	i = 2;
	s = ft_memalloc(sizeof(t_opt));
	h = ft_memalloc(sizeof(t_hash));
	get_opt(argc, argv, s, 2);
	if (argc == 3 && s->on)
		error();
	while ((int)i < argc)
	{
		while (get_opt(argc, argv, s, i) && (int)i < argc)
			i++;
//		if (s->on && s->s)
//			shash(argv[i], h, s);
		ft_printf("i: %d argc: %d\n", i, argc);
		if ((rstdin(h) && (int)i == argc) || (s->on && s->s))
			shash(h->data, h, s);
		else if (!fhash(argv[i], h, s))
		{
			ft_printf("md5: %s: No such file or directory\n", argv[i]);
			exit(0);
		}
		zeroh(s);
		i++;
	}
	if ((int)i == argc && rstdin(h))
		shash(h->data, h, s);
}
