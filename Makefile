# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efriedma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/01 16:05:56 by efriedma          #+#    #+#              #
#    Updated: 2018/10/23 01:22:28 by efriedma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Werror -Wall -Wextra -I ft_printf/libft -I ft_printf/includes

NAME = ft_ssl

PRINTF := ft_printf/

SRCS = main.c \
       helper/pad.c \
       helper/readfile.c \
	   helper/sha256help.c \
	   md5/md5.c \
       md5/md5hash.c \
       helper/get_opt.c \
       sha256/sha256hash.c \
       sha256/sha256.c \
	   sha256/sha256n.c \
	   sha256/sha256n2.c 

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ft_printf/
	gcc $(OBJ) ft_printf/libftprintf.a -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(PRINTF) clean

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
