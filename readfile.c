/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:51:40 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/07 16:44:40 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

size_t	ft_flen(int fd)
{
	size_t	i;
	size_t	ctr;
	char	buf[1];

	ctr = 0;
	i = 0;
	while ((i = read(fd, buf, 1)) == 1)
		ctr += i;
	close(fd);
	if (!ctr)
		return (0);
	return (ctr);
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
	ft_printf("\n\n\nTotal Bytes printed %d\n", i);
}

int		ft_fread(char *str, t_hash *h)
{
	int		fd;
	size_t	asize;
	char	*afile;
	size_t	chk;

	chk = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		ft_putstr("File is not valid\n");
	else
	{
		h->name = str;
		h->fd = 1;
		asize = ft_flen(fd);
		afile = ft_strnew(asize);
		fd = open(str, O_RDONLY);
		chk = read(fd, afile, asize);
		h->data = afile;
		h->ini = asize;
		h->bytes = h->ini;
		return (1);
	}
	return (0);
}
