/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 23:35:29 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/26 23:50:02 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

void    print_bytes(void *ptr, size_t size);

unsigned int k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
   	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

unsigned int	rr(unsigned int a, unsigned int shift)
{
	return ((a >> shift) | (a << (32 - shift)));
}

void			print_bendian(t_sha *s, t_hash *h, t_opt *n)
{
	unsigned char *msg;

	if (!n->q)
		ft_printf("SHA256(%s)= ", h->name);
	msg = (unsigned char *)&s->h0;
	ft_printf("%02x%02x%02x%02x ", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char *)&s->h1;
	ft_printf("%02x%02x%02x%02x ", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char *)&s->h2;
	ft_printf("%02x%02x%02x%02x ", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char *)&s->h3;
	ft_printf("%02x%02x%02x%02x ", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char *)&s->h4;
	ft_printf("%02x%02x%02x%02x ", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char *)&s->h5;
	ft_printf("%02x%02x%02x%02x ", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char *)&s->h6;
	ft_printf("%02x%02x%02x%02x ", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char *)&s->h7;
	ft_printf("%02x%02x%02x%02x\n", msg[0], msg[1], msg[2], msg[3]);
}

void			sha256hash(t_hash *hs, t_opt *nopt)
{
	t_sha			n;
	unsigned int	a;
	unsigned int	b;
	unsigned int    c;
	unsigned int    d;
	unsigned int    e;
	unsigned int    f;
	unsigned int    g;
	unsigned int    h;
	unsigned int	temp1;
	unsigned int	temp2;
	unsigned int	s0;
	unsigned int	s1;
	unsigned int	S1;
	unsigned int	S0;
	unsigned int	maj;
	unsigned int	ch;
	size_t			ctr;
	size_t			i;
	unsigned int h0 = 0x6a09e667;
	unsigned int h1 = 0xbb67ae85;
	unsigned int h2 = 0x3c6ef372;
	unsigned int h3 = 0xa54ff53a;
	unsigned int h4 = 0x510e527f;
	unsigned int h5 = 0x9b05688c;
	unsigned int h6 = 0x1f83d9ab;
	unsigned int h7 = 0x5be0cd19;
	unsigned int *w;
	size_t	x;

	x = 0;
	w = ft_memalloc(64 * 4);
	ctr = 0;
	ft_printf("Bytes from within sha hashing function\n");
	print_bytes(hs->data, hs->bytes);
	while (ctr < hs->bytes)
	{
		ft_memcpy(w, (void*)&hs->arr[x], 64);
		i = 16;
		while (i < 64)
		{
			s0 = (RR(w[i - 15], 7)) ^ (RR(w[i - 15], 18)) ^ (w[i - 15] >> 3);
			s1 = (RR(w[i - 2], 17)) ^ (RR(w[i - 2], 19)) ^ (w[i - 2] >> 10);
			w[i] = w[i - 16] + s0 + w[i - 7] + s1;
			i++;
		}
		i = 0;
		a = h0;
		b = h1;
		c = h2;
		d = h3;
		e = h4;
		f = h5;
		g = h6;
		h = h7;
		while (i < 64)
		{
			S1 = RR(e, 6) ^ RR(e, 11) ^ RR(e, 25);
			ch = (e & f) ^ ((~e) & g);
			temp1 = h + S1 + ch + k[i] + w[i];
			S0 = RR(a, 2) ^ RR(a, 13) ^ RR(a, 22);
			maj = (a & b) ^ (a & c) ^ (b & c);
			temp2 = S0 + maj;
			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
			i++;
		}
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
		h4 += e;
		h5 += f;
		h6 += g;
		h7 += h;
		i++;
		x += 16;
		ctr += 64;
	}
	n.h0 = h0;
	n.h1 = h1;
	n.h2 = h2;
	n.h3 = h3;
	n.h4 = h4;
	n.h5 = h5;
	n.h6 = h6;
	n.h7 = h7;
	print_bendian(&n, hs, nopt);
	//	digest = h0 append h1 append h2 append h3 append h4 append h5 append h6 append h7;
}
