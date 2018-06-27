# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efriedma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/01 16:05:56 by efriedma          #+#    #+#              #
#    Updated: 2018/06/26 20:51:11 by efriedma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -g -Werror -Wall -Wextra -I ft_printf/libft -I ft_printf/includes

NAME = ft_ssl

SRCS = main.c \
       pad.c \
       readfile.c \
       md5.c \
       md5hash.c \
       get_opt.c \
       sha256hash.c \
       sha256.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -g *.o ft_printf/libftprintf.a -o $(NAME)
	@make -C ft_printf

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean $(NAME)
