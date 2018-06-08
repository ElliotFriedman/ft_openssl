/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 19:18:29 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/08 16:09:05 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

const unsigned int K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

const int s[64] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21};

unsigned int		leftrotate(unsigned int x, int c)
{
	return ((x << c) | (x >> (32 - c)));
}

void	hash(t_hash *h)
{
	unsigned int a0 = 0x67452301;
	unsigned int b0 = 0xefcdab89;
	unsigned int c0 = 0x98badcfe;
	unsigned int d0 = 0x10325476;
	unsigned int A;
	unsigned int B;
	unsigned int C;
	unsigned int D;
	int	i;
	unsigned int	F;
	unsigned int g;
	size_t	d;
	unsigned int	ctr;
	unsigned char	*msg;

	ctr = 0;
	d = 0;
	while (d < h->bytes)
	{  
		i = 0;
		A = a0;
		B = b0;
		C = c0;
		D = d0;
		while (i < 64)
		{
			if (i <= 15)
			{
				F = (B & C) | ((~B) & D);
				g = i;
			}
			else if (i <= 31)
			{
				F = (D & B) | ((~D) & C);
				g = (5 * i + 1) % 16;
			}
			else if (i <= 47)
			{
				F = B ^ C ^ D;
				g = (3 * i + 5) % 16;
			}
			else if (i <= 63)
			{
				F = C ^ (B | (~D));
				g = (7 * i) % 16;
			}
			F = F + A + K[i] + h->arr[g + ctr];
			A = D;
			D = C;
			C = B;
			B = B + leftrotate(F, s[i]);
			i++;
		}
		ctr += 16;
		a0 += A;
		b0 += B;
		c0 += C;
		d0 += D;
		d += 64;
	}
	if (h->fd)
		ft_printf("MD5 (%s) = ", h->name);
//	printf("\n\n%s\n\n", h->name);
	msg = (unsigned char *)&a0;
	ft_printf("%02x%02x%02x%02x", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char *)&b0;
	ft_printf("%02x%02x%02x%02x", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char *)&c0;
	ft_printf("%02x%02x%02x%02x", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char *)&d0;
	ft_printf("%02x%02x%02x%02x\n", msg[0], msg[1], msg[2], msg[3]);
	//caller will handle all memory
	h->fd = 0;
}
