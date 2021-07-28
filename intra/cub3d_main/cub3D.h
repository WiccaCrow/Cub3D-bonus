#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx/mlx.h"
// # include "../mlx/mlx.h"
# include "map/gnl/get_next_line.h"

typedef struct s_sprite {
	int		x;
	int		y;
	float	dist;
	int		i;
}	t_spr;

typedef struct s_move {
	double	a;
	double	w;
	double	d;
	double	s;
	double	arrow_l;
	double	arrow_r;	
}	t_move;

typedef struct s_img {
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		b_p_p;
	int		line_l;
	int		endian;
}	t_img;

typedef struct s_mlx {
	void			*mlx;
	void			*win;
	char			*argv1;
	t_move			move;
	t_img			frame;
	t_img			texture_nswe_s[5];
	int				fd;
	char			*line;
	char			*free_line;
	int	r_xy[2];
	int				f_rgb[3];	
	int				c_rgb[3];
	int				does_paste_r;
	int				does_paste_f;
	int				does_paste_c;
	char			nswe_s[6];
	int				nb_lines;
	int				len_str_max;
	char			**map;
	char			player;
	unsigned int	i;
	int				ii;
	double			start_pi;
	char			wall_color;
	int				nb_sprite;
	double			move_x;
	double			move_y;
	float			x_pl;
	float			y_pl;
	float			x_w;
	float			y_w;
	double			move_round;
	float			ray_length;
	t_spr			*sprite_data;
	float			*dist_wall;
	float			k_view_hight;
	int		argv2;
}	t_mlx;

void			start_mlx(t_mlx *all);
void			start_move_sprite_wall(t_mlx *all);
void			start_mlx_texture(t_mlx *all);
void			check_extention_argv(char *argv, char *cub_flag, int nb);
void			check_empty_line_beetwen_options(t_mlx *all, int *i,
					int *q_gnl);
void			parser_valid_argv1(t_mlx *all, int q_gnl, int gnl, int i);
void			check_screen_size(t_mlx *all);
void			ft_mlx_functions(t_mlx *all);
void			parser_r_f_c(t_mlx *all, int i);
void			paste_r_f_c_part1(t_mlx *all, int *rfc,
					char c, int iter);
void			paste_r_f_c_error(t_mlx *all, int iter);
void			paste_r_f_c_part2(t_mlx *all, int *rfc,
					char comma_space, int iter);
void			paste_no_so_we_ea_s(t_mlx *all, int i);
void			map(t_mlx *all, int q_gnl);
unsigned int	atoi_only_digit(t_mlx *all, unsigned long int n);
void			push_texture_no_so_we_ea_s(t_mlx *all, char *str);
void			texture1(t_mlx *mlx_win, char *str, int flag, char *extension);
void			texture2(t_mlx *mlx_win, char *str, int flag, int fd);
void			check_paste_map_options(t_mlx *all);
void			paste_map_part1(t_mlx *all);
void			paste_map_part2(t_mlx *all, int	i, int j, int gnl);
void			closed_map(t_mlx *all, int i, int j);
void			nb_valid_map_lines(t_mlx *all, int q_gnl, int gnl, char *line);
char			map_char_around_space(t_mlx *all, int i, int j,
					int around_space);
char			*ft_strchr(const char *s, int c);
void			check_valid_every_maps_str(t_mlx *all, char *str);
void			sprite_wall_zero(t_mlx *all);
void			find_x_y_player(t_mlx *all, float x, float y);
int				key_press(int keycode, t_mlx *mlx_win);
int				key_release(int keycode, t_mlx *mlx_win);
int				render_next_frame(t_mlx *mlx_win);
void			move_adws(t_mlx *all, int ws, double ang_adws, float move_y);
void			check_move_stop(t_mlx *all, float *move_x, float *move_y);
void			drow_frame_3d(t_mlx *mlx_win, double	angle);
double			ang_correct(double angle);
void			find_wall(t_mlx *mlx_win, double angle);
double			intersections_v1(t_mlx *all, double ang_pi, double ang_cor);
int				intersections_v2(t_mlx *all, double *xp, double *yp, double a);
double			intersections_h1(t_mlx *all, double ang_pi);
int				intersections_h2(t_mlx *all, double *xp, double *yp, double b);
int				intersections_h3_wall_color(t_mlx *all, double *xp,
					double *yp, double ang_pi);
double			intersections_h4(t_mlx *all, double ang_pi,
					double xp, double yp);
void			drow_wall_floor_ceil(t_mlx *mlx_win, float wall_height,
					float pl_height, float x);
void			sprite_drow1(t_mlx *all, float dist_plane, int j);
void			sprite_fill_struct(t_mlx *all, float xp, float yp);
float			sprite_i(t_mlx *all, float xp, float yp, double angle_view);
int				check_new_sprite(t_mlx *all, int xp, int yp);
int				create_trgb(int t, int r, int g, int b);
int				color_wall(t_mlx *all, float height_w, int h, float k_pl_w);
void			my_mlx_pix_put(t_img *map, int x, int y, int color);
unsigned int	my_mlx_pix_take(t_img *map, int x, int y);
t_spr			*sprite_sort(t_mlx *all, int i, int j, int k);
void			sprite_drow2(t_mlx *all, float height, float x, int j);
int				color_sprite(t_mlx *all, float height_s, int h, int j);
void			save_bmp(t_mlx *mw);
void			bmp_header(int fd, int width, int height);
char			*reverse_4_byte(int bmp_size_or_color, char *buf);
char			*reverse_2_byte(int bmp_size_or_color, char *buf);
void			bmp_image(int fd, int width, int height, t_mlx *mw);
void			pointer_null(t_mlx *all);
int				exit_clean(t_mlx *all, int i, int ii);

# define	KEY_LEFT_A 97//0// движение игрока. коды клавиш
# define	KEY_UP_W 119//13
# define	KEY_RIGHT_D 100//2
# define	KEY_DOWN_S 115//1
# define	KEY_ESC 65307//53
# define	KEY_LEFT_ARROW 65361//123
# define	KEY_UP_ARROW 65362//126
# define	KEY_RIGHT_ARROW 65363//124
# define	KEY_DOWN_ARROW 65364//125
# define    KEY_M 109//46
// # define	KEY_SPACE
# define	X11_EVENTS_KEYPRESS 2
# define	X11_EVENTS_KEYREL 3
# define	X11_EVENTS_EXIT 17
# define	SIZE_BLOCK 64//брать только четные
# define	FOV 66.851599
# define	SPEED 0.15
# define	ROUND 0.04567//0.069813
# define	PL_HEIGHT 32
# define	COLOR_SKIP 0x00FFFFF0
# define	PL_HEIGHT_DOWN 15
# define	PL_HEIGHT_UP 45

#endif
