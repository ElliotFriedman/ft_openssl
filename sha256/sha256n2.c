/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256n2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 23:52:32 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/23 01:26:11 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

unsigned int	swap_endian(unsigned int num)
{
	unsigned int	b[4];

	b[0] = (num & 0x000000ff) << 24u;
	b[1] = (num & 0x0000ff00) << 8u;
	b[2] = (num & 0x00ff0000) >> 8u;
	b[3] = (num & 0xff000000) >> 24u;
	return (b[0] | b[1] | b[2] | b[3]);
}

void			swap(t_hash *h)
{
	size_t			i;
	unsigned char	*m;

	m = 0;
	i = 0;
	while (i < ((h->bytes) / 4))
	{
		h->arr[i] = swap_endian(h->arr[i]);
		i++;
	}
}

void			zer0h(t_opt *h, t_hash *hash)
{
	hash->pipe = 0;
	h->s = 0;
}
