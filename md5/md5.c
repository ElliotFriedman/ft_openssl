/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:21:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/12/17 00:58:41 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

t_hash		h;
t_opt		s;
	
int		shash(char *hash1, t_hash *h, t_opt *new)
{
	if (new->p && hash1 && h->pipe)
		ft_printf("%s", h->data);
	if (!hash1)
		return (0);
	if (!h->pipe)
		h->data = ft_strdup(hash1);
	h->name = hash1;
	if (h->data)
		h->bytes = ft_strlen(h->data);
	h->ini = h->bytes;
	epad(h);
	h->arr = (unsigned int *)h->data;
	hash(h, new);
	ft_memdel((void**)&h->data);
	h->pipe = 0;
	return (1);
}

int		fhash(char *hash1, t_hash *h, t_opt *new, int *file)
{
	*file += 1;
	if (!ft_fread(hash1, h))
		return (0);
	h->name = hash1;
	epad(h);
	h->arr = (unsigned int *)h->data;
	hash(h, new);
	ft_memdel((void**)&h->data);
	return (1);
}

int		zeroh(t_opt *h, t_hash *hash)
{
	hash->pipe = 0;
	h->s = 0;
	return (1);
}

void	md5start(char **av, int a)
{
	int			file;

	//if argc is 1 or 2, doesn't matter, read from standard input
	//
	//else check for flags and iterate to next option
	file = 0;
	h.i = get_opt_loop(2, a, av, &s);
	if ((h.i != 2 && rstdin(&h)) || (((int)h.i == a) && (s.p || rstdin(&h))))
		shash(h.data, &h, &s);
	else if (a == (int)h.i && rkey(&h) && (s.q = 1))
		shash(h.data, &h, &s);
	else if (a == (int)h.i && rstdin(&h) && (h.pipe = 1) && (s.p = 1))
		shash(h.data, &h, &s);
	while ((int)h.i < a)
	{
		while (!file && get_opt(a, av, &s, h.i) && (int)h.i < a)
			h.i++;
		if (!file && s.on && s.s)
			shash(av[h.i], &h, &s);
		else if (!fhash(av[h.i], &h, &s, &file))
			ft_printf("ft_ssl: md5: %s: No such file or directory\n", av[h.i]);
		else if (!file && ((int)h.i == a && rstdin(&h)))
			shash(h.data, &h, &s);
		zeroh(&s, &h);
		h.i++;
	}
}
