/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 15:48:33 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/08 15:46:03 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

const int total = 1;

void	init_command(t_type **arr, size_t index, char *str, void *command)
{
	arr[index]->name = ft_strdup(str);
	arr[index]->ptr = command;
}

t_type	*create(t_type **s)
{
	size_t	i;

	i = 0;
	s = ft_memalloc(sizeof(t_type) * total);
	while (i < total)
	{
		s[i] = ft_memalloc(sizeof(t_type));
		i++;
	}
	i = 0;
	while (i < total)
	{
		s[i]->name = ft_memalloc(sizeof(char *));
		s[i]->ptr = ft_memalloc(sizeof(void *));
		i++;
	}
	init_command(s, 0, "md5", md5start);
	//	init_command(new, 1, "sha256", sha256start);
	return (s[0]);
}

int		dispatch(t_type *t, int argc, char **argv)
{
	void (*x) (char**, int);

	if (!ft_strcmp(t->name, argv[1]))
	{
		x = (void (*) (char**, int))(t->ptr);
		x(argv, argc);
		return (1);
	}
	return (0);
}

void	free_struct(t_type **done)
{
	size_t	i;

	i = 0;
	while (i < total)
	{
		free(done[i]->name);
//		free(done[i]->ptr);
		free(done[i]);
		i++;
	}
//	free(done);
}

int		main(int argc, char **argv)
{
	t_type	*s;
	size_t	i;

	i = 0;
	if (argc >= 2)
	{
		s = create(&s);
		i = 0;
		while (i < total && ft_strcmp(s[i].name, argv[1]))
			i++;
		if (i == total || !dispatch(&s[i], argc, argv))
		{
			ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", argv[1]);
			ft_printf("\nStandard commands:\n\nMessage Digest commands:\nmd5\nsha256\n");
		}
		free_struct(&s);
	}
	else
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}