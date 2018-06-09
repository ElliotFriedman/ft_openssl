/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 23:35:29 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/08 22:43:55 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

unsigned int h0 = 0x6a09e667;
unsigned int h1 = 0xbb67ae85;
unsigned int h2 = 0x3c6ef372;
unsigned int h3 = 0xa54ff53a;
unsigned int h4 = 0x510e527f;
unsigned int h5 = 0x9b05688c;
unsigned int h6 = 0x1f83d9ab;
unsigned int h7 = 0x5be0cd19;

const unsigned int k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};


void	sha256hash(something)
{
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
	size_t			ctr;

	ctr = 0;
	while (ctr < h->bytes)
	{
		create a 64-entry message schedule array w[0..63] of 32-bit words
			(The initial values in w[0..63] don't matter, so many implementations zero them here)
			copy chunk into first 16 words w[0..15] of the message schedule array

			Extend the first 16 words into the remaining 48 words w[16..63] of the message schedule array:
			while (i < 63)
			{
				s0 = (w[i-15] rightrotate 7) ^ (w[i-15] rightrotate 18) ^ (w[i-15] >> 3);
        		s1 = (w[i-2] rightrotate 17) xor (w[i-2] rightrotate 19) ^ (w[i-2] >> 10);
				w[i] = w[i - 16] + s0 + w[i - 7] + s1;
				a = h0;
				b = h1;
				c = h2;
				d = h3;
				e = h4;
				f = h5;
				g = h6;
				h = h7;
				while (i < 63)
				{
					S1 = (e rightrotate 6) xor (e rightrotate 11) xor (e rightrotate 25);
					ch = (e & f) ^ ((~e) & g);
					temp1 = h + S1 + ch + k[i] + w[i];
					S0 = (a rightrotate 2) xor (a rightrotate 13) xor (a rightrotate 22);
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
				h0 = h0 + a;
				h1 = h1 + b;
				h2 = h2 + c;
				h3 = h3 + d;
				h4 = h4 + e;
				h5 = h5 + f;
				h6 = h6 + g;
				h7 = h7 + h;
				i++;
			}
		ctr += 16;
	}
	print_bendian();
	digest = h0 append h1 append h2 append h3 append h4 append h5 append h6 append h7;
}
