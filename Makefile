# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:54:00 by rpinoit           #+#    #+#              #
#    Updated: 2018/03/09 13:40:23 by rpinoit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

FLG = -Wall -Wextra -Werror -lpthread -Ofast

SRC = srcs/main.c \
	  srcs/error.c \
	  srcs/raytracer.c \
	  srcs/vector_utilities.c \
	  srcs/intersection.c \
	  srcs/light.c \
	  srcs/parser.c \
	  srcs/parser_obj.c \
	  srcs/parser_utils.c \
	  srcs/parser_fill.c \
	  srcs/math_utilities.c \
	  srcs/pixel.c \
	  srcs/obj_normal.c \
	  srcs/light_phong_shading.c \
	  srcs/vector_rotate.c \
	  srcs/draw.c \
	  srcs/hook.c \
	  srcs/hook2.c \
	  srcs/anti_alias.c 

OBJ = $(SRC:%.c=%.o)

INC = -I./incs \
	  -I./libft/ \
	  -I/usr/include \
	  -I/minilibx_macos/

LIB = -L./libft \
	  -L./minilibx_macos/

all: $(NAME)

$(NAME):
	make -C minilibx_macos
	make -C libft
	gcc $(FLG) $(LIB) $(INC) $(SRC) -lm -lft -lmlx -framework OpenGL -framework Appkit -o $(NAME)

clean:
	make -C libft clean
	rm -f $(NAME)

fclean: clean
	make -C libft fclean
	rm -rf $(OBJ)

re: clean all
