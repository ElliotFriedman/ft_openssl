/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 14:17:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/27 12:23:58 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

 void    print_bytes(void *ptr, size_t size);


static void ft_sha256_add_length(char *data, t_hash *h)
{
	unsigned long long length; 
	
	length = h->ini * 8;
	data[63] = length;
	data[62] = length >> 8;
	data[61] = length >> 16;
	data[60] = length >> 24;
	data[59] = length >> 32;
	data[58] = length >> 40;
	data[57] = length >> 48;
	data[56] = length >> 56;
}

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
	ft_sha256_add_length((h->data + h->bytes - 64), h);
	//ft_memcpy(&h->data[h->bytes - 8], (void*)max, 8);
	
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
