# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/28 14:55:07 by seruiz            #+#    #+#              #
#    Updated: 2021/02/03 14:58:56 by seruiz           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: re, clean, fclean, all, bonus

NAME= cub3d

SRC_FILE=	./src/engine/ft_cast_wall.c\
		./src/parsing/ft_init_ch.c\
		./src/parsing/ft_parse_3.c\
		./src/engine/ft_cub3d_2.c\
		./src/parsing/ft_itoa_strdup.c\
		./src/parsing/ft_parse_4.c\
		./src/engine/ft_cube3d.c\
		./src/engine/sprite/ft_lod_close.c\
		./src/engine/ft_raycast.c\
		./src/engine/ft_draw_wall_e.c\
		./src/engine/sprite/ft_lod_far.c\
		./src/engine/sprite/ft_sprite.c\
		./src/engine/ft_draw_wall_n.c\
		./src/engine/sprite/ft_lod_mid.c\
		./src/engine/sprite/ft_sprite_2.c\
		./src/engine/ft_draw_wall_s.c\
		./src/engine/sprite/ft_lod_midf.c\
		./src/engine/ft_texture.c\
		./src/engine/ft_draw_wall_w.c\
		./src/engine/ft_move.c\
		./src/engine/ft_turn_key.c\
		./src/parsing/ft_error.c\
		./src/parsing/ft_parse.c\
		./src/utils/ft_wrmalloc.c\
		./src/parsing/ft_gnl_file.c\
		./src/parsing/ft_parse_2.c\
		./src/parsing/ft_parse_5.c\
		./src/utils/get_next_line/get_next_line.c\
		./src/utils/get_next_line/get_next_line_utils.c\
		./src/screenshot/print_image.c\
		./src/utils/ft_memcpy.c\
		./src/utils/ft_putstr_fd.c\
		./src/engine/main.c

OBJ=${SRC_FILE:.c=.o}

INCLUDES= ./minilibx/libmlx.a\
		./includes/cube3d.h\
		./includes/print_image.h\
		./includes/get_next_line.h

all: $(NAME)

all bonus : $(NAME)

$(NAME): ${OBJ}
	@gcc -Lminilibx -lmlx -framework OpenGL -framework AppKit -o cub3D ${OBJ}

%.o: %.c
	@gcc -c -Wall -Werror -Wextra -c $< -o $@

clean:
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME) $(BONUS)

re: fclean all