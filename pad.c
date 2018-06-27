/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 14:17:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/26 21:08:00 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

 void    print_bytes(void *ptr, size_t size);

void	block_end(t_hash *h)
{
	char				*tmp;
	char				*ctmp;
	unsigned long long	*max;

	ft_printf("bytes: %d h->ini: %d\n",h->bytes, h->ini);
	
	max = ft_memalloc(8);
	*max = 8 * h->ini;
	
	h->bytes += 8;
	tmp = h->data;

	ctmp = ft_memalloc(h->bytes);
	
	h->data = ft_memcpy(ctmp, h->data, h->bytes - 8);
	ft_memcpy(&h->data[h->bytes - 8], (void*)max, 8);
	
	//h->data = ft_memcpy(ctmp, (void*)max, 8);
	
	//h->data = ctmp;

//	ft_printf("ctpm: %p tmp: %p\n", &ctmp, &tmp);
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
	h->data = (char *)ft_memcpy(snew, h->data, h->bytes - 1);
	free(tmp);
	return (h->data);
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
	print_bytes((void *)h->data, h->bytes);
	
	dif += 8;
	while (dif % 512 != 448)
	{
		h->data = add_byte(h);
		dif += 8;
	}
	print_bytes((void *)h->data, h->bytes);
	free(buf);
	block_end(h);
}
