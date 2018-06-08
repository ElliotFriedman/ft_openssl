/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 14:17:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/06 15:47:44 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

void	block_end(t_hash *h)
{
	char	*tmp;
	char	*ctmp;
	unsigned long long		*max;

	max = ft_memalloc(8);
	*max = 8 * h->ini;
	h->bytes += 8;
	tmp = h->data;
	ctmp = ft_memalloc(h->bytes);
	h->data = ft_memcpy(ctmp, h->data, h->bytes - 8);
	h->data = ft_memcpy(&h->data[h->bytes - 8], (void*)max, 8);
	h->data = ctmp;
	free(tmp);
	free(max);
}

char	*add_byte(t_hash *h)
{
	char	*snew;
	char	*tmp;

	tmp = h->data;
	h->bytes++;
	snew = ft_memalloc(h->bytes);
	h->data = (char *)ft_memcpy(snew, h->data, h->bytes);
	free(tmp);
	return (h->data);
}

void	p_bytes(void *ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%#2p ", ((unsigned char *)ptr)[i]);
		i++;
	}
	ft_printf("\n\n\n		-----Total Bytes printed %d-----\n\n", i);
}



void	epad(t_hash *h)
{
	int				dif;
	unsigned char	*buf;
	size_t			tmp;

	buf = ft_umalset(1, 128);
	tmp = h->bytes;
	dif = (h->bytes * 8) % 512;
	ft_memcpy(&h->data[h->bytes], buf, 1);
	h->bytes++;
	dif += 8;
	while (dif % 512 != 448)
	{
		h->data = add_byte(h);
		dif += 8;
	}
//	p_bytes(h->data, h->bytes);
	free(buf);
	block_end(h);
//	p_bytes(h->data, h->bytes);
}
