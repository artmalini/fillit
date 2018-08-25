# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/26 11:24:52 by gvynogra          #+#    #+#              #
#    Updated: 2017/11/26 11:24:59 by gvynogra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
GC = gcc
CFLAGS = -Wall -Wextra -Werror -I libft
SRC = fillit.c \
	  main.c \
	  check.c \
	  coords.c \
	  tetris.c \
	  map.c \

OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(OBJ):	%.o: %.c
	$(GC) -c $(CFLAGS) $< -o $@

$(LIBFT):
	@make -C libft

$(NAME): $(LIBFT) $(OBJ)
	$(GC) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
