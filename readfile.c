/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:51:40 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/26 20:53:31 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

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

size_t	ft_flen(int fd)
{
	size_t	i;
	size_t	ctr;
	char	buf[1000000];

	ctr = 0;
	i = 0;
	while ((i = read(fd, buf, 1000000)) > 0)
		ctr += i;
	close(fd);
	return (ctr);
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
		return (0);
		//ft_putstr("File is not valid\n");
	else
	{
		h->fd = 1;
		asize = ft_flen(fd);
		afile = ft_strnew(asize);
		fd = open(str, O_RDONLY);
		chk = read(fd, afile, asize);
		h->data = afile;
		h->ini = asize;
		h->bytes = h->ini;
		close(fd);
	 	ft_printf("size of file = %d\n", asize);
		h->arr = (unsigned int *)h->data;
	//	swap(h);
		print_bytes((void*)h->data, h->bytes);
		return (1);
	}
	return (0);
}

int		rkey(t_hash *h)
{
	char	*buf;
	char	*str;
	char	*tmp;

	str = ft_strnew(0);
	h->bytes = 0;
	buf = ft_memalloc(2);
	while (read(0, buf, 1) == 1)
	{
		tmp = str;
		str = ft_strjoin(str, buf);
		h->bytes++;
		free(tmp);
	}
	str[h->bytes] = 0;
	ft_memdel((void**)&buf);
	h->data = str;
	h->ini = h->bytes;
	return (1);
}

int		rstdin(t_hash *h)
{
	char	buf[2];
	char	*str;
	char	*tmp;

	str = 0;
	h->bytes = 0;
	buf[1] = 0;
	if (!isatty(0))
	{
		str = ft_strnew(0);
		while (read(0, buf, 1) == 1)
		{
			tmp = str;
			str = ft_memjoin(str, buf, h->bytes, 1);
			h->bytes++;
			free(tmp);
		}
		str[h->bytes] = 0;
		h->pipe = 1;
		h->data = str;
	}
	h->ini = h->bytes;
	return (h->bytes);
}
