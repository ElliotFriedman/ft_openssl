/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_endian.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 13:35:31 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/25 14:03:53 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

unsigned int	swap_endian(unsigned int num)
{
	unsigned int	b[4];

	b[0] = (num & 0x000000ff) << 24u;
	b[1] = (num & 0x0000ff00) << 8u;
	b[2] = (num & 0x00ff0000) >> 8u;
	b[3] = (num & 0xff000000) >> 24u;

	return (b[0] | b[1] | b[2] | b[3]);
}

void	print_bytes(void *ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%#2p ", ((unsigned char *)ptr)[i]);
		i++;
	}
	ft_printf("\n");
}

int main()
{
	unsigned int a = 1;
	void *ptr;


	print_bytes((void*)&a, 4);
	
	a = swap_endian(a);
	print_bytes((void*)&a, 4);
	ft_putchar('\n');
	return (0);
}
