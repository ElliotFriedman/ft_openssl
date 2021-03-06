/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:02:27 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/23 00:12:25 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int		opt(char *argv, t_opt *new)
{
	int	fin;

	fin = 0;
	if (ft_strchr(argv, (int)'p') && ++fin)
		new->p = 1;
	if (ft_strchr(argv, (int)'q') && ++fin)
		new->q = 1;
	if (ft_strchr(argv, (int)'r') && ++fin)
		new->r = 1;
	if (ft_strchr(argv, (int)'s') && ++fin)
		new->s = 1;
	if ((new->s || new->r || new->q || new->p) && fin)
	{
		new->on = 1;
		return (1);
	}
	return (0);
}

int		get_opt(int argc, char **argv, t_opt *new, int i)
{
	while (i < argc && open(argv[i], O_RDONLY) == -1)
	{
		if (argv[i][0] == '-' && opt(argv[i], new))
			return (1);
		else
			return (0);
		i++;
	}
	return (0);
}
