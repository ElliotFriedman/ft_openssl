# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efriedma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/01 16:05:56 by efriedma          #+#    #+#              #
#    Updated: 2018/06/07 17:25:34 by efriedma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -g -fsanitize=address -Werror -Wall -Wextra -I ft_printf/libft -I ft_printf/includes

NAME = ft_openssl

SRCS = main.c \
	   pad.c \
	   readfile.c \
	   md5.c \
	   md5hash.c \
	   get_opt.c \


OBJ = $(SRCS:.c=.o)

all: $(NAME)
	
$(NAME): $(OBJ)
	@make -C ft_printf
	gcc -g -fsanitize=address *.o ft_printf/libftprintf.a -o $(NAME)

clean:
	rm $(OBJ)
	make -C ft_printf clean

fclean: clean
	make -C ft_printf fclean
	rm $(NAME)