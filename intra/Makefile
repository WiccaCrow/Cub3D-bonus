NAME = cub3D

MLX = -lm -lmlx -lXext -lX11

FLAGS = -Wall -Wextra -O2

SRC = \
main_1_main.c \
main_2_start_all.c \
map/fill_all_except_the_map.c \
map/libft_add_func.c \
map/fill_map_part1.c \
map/fill_map_part2.c \
map/gnl/get_next_line_utils.c \
map/gnl/get_next_line.c \
graphic/mlx_1_start.c \
graphic/mlx_2_raycasting.c \
graphic/mlx_3_raycasting_intersection_horiz.c \
graphic/mlx_4_raycast_inters_vertical_and_drow_w_f_c.c \
graphic/mlx_5_texture.c \
graphic/mlx_6_sprite.c \
graphic/mlx_7_sprite_drow.c \
graphic/mlx_8_save_bmp.c


ifdef MAKE_BONUS
FOLDER = ./cub3d_bonus/
SRC1 = $(addprefix $(FOLDER), $(SRC))
SRC1 += $(addprefix $(FOLDER), graphic/bonus_correct_move.c graphic/bonus_itoa.c graphic/bonus_drow_map.c main_3_start_all.c)
HEAD = ./cub3d_bonus/
else
FOLDER = ./cub3d_main/
SRC1 = $(addprefix $(FOLDER), $(SRC))
HEAD = ./cub3d_main/
endif

OBJ = $(SRC1:.c=.o)

all: $(NAME)

bonus: ; $(MAKE) MAKE_BONUS=0 all

%.o: %.c$(HEAD)
	# gcc $(FLAGS) -Imlx -c $< -o $@ -I$(HEAD) $@ -c $<
	# gcc $(FLAGS) -I$(HEAD) -I./minilibx -c $(OBJ) -o $@ -L./minilibx $(MLX)
	gcc -g -I$(HEAD) -I./minilibx -c $(@:.o=.c) -o $@ -L./minilibx -lm -lmlx -lXext -lX11

# $(OBJ): %.o: %.c $(HEAD)
# 	gcc $(FLAGS) -I$(HEAD) -c $< -o $@

MINILIBX = make -C minilibx

$(NAME): $(OBJ) 
		$(MINILIBX)
	# gcc $(MLX) -o $(NAME) $(OBJ)
		gcc -g -I$(HEAD) -I./minilibx -o $(NAME) $(OBJ) -L./minilibx $(MLX)

clean: ; rm -rf $(OBJ) ; make clean -C minilibx
cleanbonus: ; $(MAKE) MAKE_BONUS=0 clean

fclean:	clean ; rm -rf $(NAME)
fcleanbonus: ; $(MAKE) MAKE_BONUS=0 clean ; rm -rf $(NAME)

re: fclean all
rebonus: ; $(MAKE) MAKE_BONUS=0 fclean all

.PHONY: all clean fclean re bonus cleanbonus fcleanbonus rebonus
