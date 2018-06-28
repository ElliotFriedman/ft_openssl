# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efriedma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/01 16:05:56 by efriedma          #+#    #+#              #
#    Updated: 2018/06/27 23:54:55 by efriedma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-fsanitize=address 

CFLAGS = -g -fsanitize=address -Werror -Wall -Wextra -I ft_printf/libft -I ft_printf/includes

NAME = ft_ssl

SRCS = main.c \
       helper/pad.c \
       helper/readfile.c \
	   helper/sha256help.c \
	   md5/md5.c \
       md5/md5hash.c \
	   md5/md5n.c \
       helper/get_opt.c \
       sha256/sha256hash.c \
       sha256/sha256.c \
	   sha256/sha256n.c \
	   sha256/sha256n2.c \

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -g *.o -fsanitize=address md5/*.o sha256/*.o helper/*.o ft_printf/libftprintf.a -o $(NAME)
	@make -C ft_printf

clean:
	rm *.o && rm md5/*.o && rm sha256/*.o && rm helper/*.o

fclean: clean
	rm $(NAME)

re: fclean $(NAME)
