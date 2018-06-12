/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 17:04:26 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/11 17:55:44 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

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
//	printf("\n\n%s\n\n", h->name);
	sha256hash(h, s);
	return (1);
}

int		f256hash(char *hash1, t_hash *h, t_opt *s)
{
	if (!ft_fread(hash1, h))
		return (0);
	h->name = hash1;
	printf("\n\n%s\n\n", h->name);
	epad(h);
	h->arr = (unsigned int *)h->data;
	sha256hash(h, s);
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
	if (argc == 3 && s->on)
		err();
	while ((int)i < argc)
	{
		while (get_opt(argc, argv, s, i) && (int)i < argc)
			i++;
		if (s->on && s->s)
			s256hash(argv[i], h, s);
				//i < argc could be incorrect
		else if ((int)i < argc && !f256hash(argv[i], h, s))
		{
			ft_printf("md5: %s: No such file or directory\n", argv[i]);
			exit(0);
		}
		zero(s);
		i++;
	}
}
