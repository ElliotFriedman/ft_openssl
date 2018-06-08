/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:21:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/08 14:30:04 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

//./ft_openssl md5 -s -hello -s hi

void	shash(char *thash, t_hash *h, int i)
{
	printf("\n%s %d\n", thash, i);
	h->data = ft_strdup(thash);
	h->ini = ft_strlen(h->data);
	h->bytes = h->ini;
	epad(h);
	h->arr = (unsigned int *)h->data;
	hash(h);
	ft_memdel((void**)&h->data);
}

int		fhash(char *fhash, t_hash *h)
{
	if (!ft_fread(fhash, h))
		return (0);
	h->name = fhash;
	epad(h);
	h->arr = (unsigned int *)h->data;
	hash(h);
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

void	md5start(char **argv, int argc)
{
	int	fd;
	t_hash	*h;
	t_opt	*new;
	size_t	i;

	i = 2;
	new = ft_memalloc(sizeof(t_opt));
	h = ft_memalloc(sizeof(t_hash));
	fd = 0;
	get_opt(argc, argv, new, 2);
	if (argc == 3 && new->on)
	{
		ft_printf("md5: option requires an argument -- s\n");
		ft_printf("usage: md5 [-pqrtx] [-s string] [files ...]\n");
		exit(0);
	}
	while ((int)i < argc)
	{
		while (get_opt(argc, argv, new, i) && (int)i < argc)
			i++;
		if (new->on && new->s)
			shash(argv[i], h, i);
		else if (!fhash(argv[i], h))
		{
			ft_printf("md5: %s: No such file or directory\n", argv[i]);
			exit(0);
		}
		zeroh(new);
		i++;
	}
}
