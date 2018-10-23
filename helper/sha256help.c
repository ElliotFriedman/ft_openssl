/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 22:17:16 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/23 00:42:15 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

unsigned int g_z[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
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

void			print_bendian(t_sha *s)
{
	unsigned char	*msg;
	size_t			i;

	i = 0;
	while (i < 8)
	{
		msg = (unsigned char *)&s->h0[i];
		ft_printf("%02x%02x%02x%02x", msg[3], msg[2], msg[1], msg[0]);
		i++;
	}
}

void			handle_out1(t_sha *s, t_hash *h, t_opt *n)
{
	if (n->q || (h->pipe))
		print_bendian(s);
	else if (!n->q && !n->r && !n->s)
	{
		ft_printf("SHA256(%s)= ", h->name);
		print_bendian(s);
	}
	else if (!n->q && n->r && !n->s)
	{
		print_bendian(s);
		ft_printf(" *%s", h->name);
	}
	else if (n->on && n->s && !n->q && !n->r)
	{
		ft_printf("SHA256(%s)= ", h->name);
		print_bendian(s);
	}
	ft_putchar('\n');
}

void			whiled(t_sha *n, size_t i, unsigned int *w)
{
	n->ss1 = RR(n->e, 6) ^ RR(n->e, 11) ^ RR(n->e, 25);
	n->ch = (n->e & n->f) ^ ((~n->e) & n->g);
	n->temp1 = n->h + n->ss1 + n->ch + g_z[i] + w[i];
	n->ss0 = RR(n->a, 2) ^ RR(n->a, 13) ^ RR(n->a, 22);
	n->maj = (n->a & n->b) ^ (n->a & n->c) ^ (n->b & n->c);
	n->temp2 = n->ss0 + n->maj;
	n->h = n->g;
	n->g = n->f;
	n->f = n->e;
	n->e = n->d + n->temp1;
	n->d = n->c;
	n->c = n->b;
	n->b = n->a;
	n->a = n->temp1 + n->temp2;
}

void			t_sha_init(t_sha *n)
{
	n->h0[0] = 0x6a09e667;
	n->h0[1] = 0xbb67ae85;
	n->h0[2] = 0x3c6ef372;
	n->h0[3] = 0xa54ff53a;
	n->h0[4] = 0x510e527f;
	n->h0[5] = 0x9b05688c;
	n->h0[6] = 0x1f83d9ab;
	n->h0[7] = 0x5be0cd19;
}
