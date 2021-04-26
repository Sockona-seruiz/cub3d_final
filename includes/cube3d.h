/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:07:24 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/04 12:09:06 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUBE3D_H
# define FT_CUBE3D_H
# define NOERROR -1
# define MALLOC 1
# define MULTITEX 2
# define MULTICH 3
# define NOTCLOSED 4
# define WRGCHARAC 6
# define NOCH 7
# define FLOORERR 8
# define FLOORMISS 14
# define ROOFERR 9
# define ROOFMISS 13
# define RESERR 10
# define OORCOLOR 11
# define MISSINFO 12
# define IMGERR 15
# define SAVEERR 16
# define MAPERR 17
# define MAX_X 2560
# define MAX_Y 1440
# define MIN_RES 10
# define MAP_RES 64
# define ESC 53
# define W 13
# define UP 126
# define A 0
# define LEFT 123
# define S 1
# define DOWN 125
# define D 2
# define RIGHT 124
# define SHIFT 257
# define R 15
# define ALT 261
# define CTRL 256
# define F12 111
# define DEG_POWER 100
# define FOV 60
# define DARKNESS 350
# define NONE 0xFF000000

# include "./mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <limits.h>

typedef struct		s_sa
{
	int				j;
	int				index;
	int				len;
	int				len_2;
}					t_sa;

typedef struct		s_col
{
	int				j;
	int				r;
	int				g;
	int				b;
}					t_col;

typedef struct		s_fillmap
{
	int				i;
	int				j;
	int				changed;
}					t_fillmap;

typedef struct		s_sdraw
{
	unsigned int	cl;
	double			size;
	int				index;
	int				i;
	int				j;
	int				view_h;
}					t_sdraw;

typedef struct		s_map_file
{
	int				ln;
	int				x;
	int				y;
	int				max;
	int				j;
	int				pos_found;
}					t_map_file;

typedef struct		s_fimg
{
	int				size_l;
	int				bpp;
	int				endian;
}					t_fimg;

typedef struct		s_sprite
{
	double			posx;
	double			posy;
	double			dist;
}					t_sprite;

typedef struct		s_sprites_info
{

	int				tex_w;
	int				tex_h;
	int				isa;
	int				frame;
	int				framebuff;
	char			*path;
	char			**anim_path;
	unsigned int	*tex;
	unsigned int	**texa;
}					t_sprite_info;

typedef struct		s_renderer
{
	void			*mlx_ptr;
	void			*win;
	int				r_wid;
	int				r_hei;
	int				r_hei_2;
	int				r_size;
	int				wid_len;
	void			*img_ptr;
	unsigned int	*img_data;
	unsigned int	*backgroundimg;
	void			*back_ptr;
	t_fimg			img;
	int				deg_power;
	unsigned int	*color_tab;
	int				step;
	t_sprite_info	*sprites_info;
	int				map_line;
}					t_renderer;

typedef struct		s_character
{
	int				save;
	int				argu;
	unsigned int	tilex;
	unsigned int	tiley;
	double			posx;
	int				posx_64;
	double			posy;
	int				posy_64;
	int				mapline;
	int				mapcol;
	float			angle_rad;
	float			fov_rad;
	short int		speed;
	int				frame;
	int				delay;
}					t_ch;

typedef	struct		s_wall
{
	int				top;
	int				bot;
}					t_wall;

typedef struct		s_point
{
	float			x;
	float			y;
	int				col;
	int				line;
}					t_point;

typedef	struct		s_col_ratio
{
	float			r;
	float			g;
	float			b;
	float			r_ratio;
	float			g_ratio;
	float			b_ratio;
}					t_col_ratio;

typedef	struct		s_key
{
	short int		w;
	short int		a;
	short int		s;
	short int		d;
	short int		r;
	short int		left;
	short int		right;
	short int		up;
	short int		down;
	short int		shift;
	short int		alt;
	short int		ctrl;
}					t_key;

typedef struct		s_map
{
	t_sprite_info	*sprite;
	int				save;
	char			**map;
	int				mapx;
	int				mapy;
	char			**file;
	int				count_line;
	int				res_x;
	int				res_y;
	char			*tex_n;
	char			*tex_e;
	char			*tex_s;
	char			*tex_w;
	char			*sprt;
	char			**sprta;
	int				issprta;
	int				frame;
	int				delay;
	int				floor;
	int				roof;
}					t_map;

typedef struct		s_tex
{
	char			*path_n;
	unsigned int	*tex_n;
	int				north_w;
	int				north_h;
	int				north_len;
	float			w_r_tex_n;
	float			h_r_tex_n;
	char			*path_s;
	unsigned int	*tex_s;
	int				south_w;
	int				south_h;
	int				south_len;
	float			w_r_tex_s;
	float			h_r_tex_s;
	char			*path_e;
	unsigned int	*tex_e;
	int				east_w;
	int				east_h;
	int				east_len;
	float			w_r_tex_e;
	float			h_r_tex_e;
	char			*path_w;
	unsigned int	*tex_w;
	int				west_w;
	int				west_h;
	int				west_len;
	float			w_r_tex_w;
	float			h_r_tex_w;
}					t_tex;

typedef struct		s_gif_info
{
	int				frames;
	int				gif_w;
	int				gif_h;
	float			gif_ratio_w;
	float			gif_ratio_h;
}					t_gif_info;

typedef struct		s_gif
{
	void			**img_ptr;
	void			**img_ptr_scaled;
	unsigned int	**texs;
	unsigned int	**tex_scaled;
	t_gif_info		*info;
}					t_gif;

typedef struct		s_darken
{
	int				r;
	int				g;
	int				b;
	int				r2;
	int				g2;
	int				b2;
}					t_darken;

typedef struct		s_ray_hit
{
	float			dist;
	float			hit_x;
	float			hit_y;
	float			tex_off_x;
	float			tex_off_y;
	char			ori;
	float			dark_r;
}					t_ray_hit;

typedef struct		s_ray_struct
{
	t_renderer		*rdr;
	t_ch			*ch;
	t_tex			*tex;
	t_key			*keys;
	t_ray_hit		hit_info;
	t_sprite		*sprite_list;
	double			*disttab;
	double			dir;
	int				spritenb;
	int				deg_power;
	char			**map;
	int				view_h;
	float			ray_step_rad;
	float			half_fov_rad;
	int				screen_dist;
	char			ori;
	unsigned int	hit_x;
	unsigned int	hit_y;
	int				up_lim;
	int				down_lim;
}					t_ray_struct;

typedef struct		s_draw_w_var
{
	int				i;
	int				ydown;
	int				ydown_back;
	double			half;
	int				yup;
	int				yup_back;
	double			line;
	int				new_line;
	int				x;
	int				wall_size_2;
	int				j;
}					t_draw_w_var;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_putstr_fd(char *s, int fd);
void				ft_set_frame(t_ray_struct *ray_s);
char				**ft_set_tex_sa(t_map *map_struct, int i,
					char **oldtex);
int					wrfree(void *ptr);
void				wrdestroy(void);
void				ft_is_closed(t_map *map_struct, t_map_file s);
void				ft_bzero_struct(t_map *map_struct);
void				*wrmalloc(unsigned long size);
unsigned int		creatergb(int r, int g, int b);
int					ft_atoi(const char *str);
void				ft_parse_inf(t_map *map_struct);
t_map				*ft_gnl_map(int fd, char *path, t_map *map_struct);
void				ft_parse_error(int erno);
void				ft_set_roof(t_map *map_struct, int i);
void				ft_set_floor(t_map *map_struct, int i);
int					ft_replace_x(t_map_file s, char **map, int i, int j);
void				ft_set_res(t_map *map_struct, int i);
char				*ft_set_tex(t_map *map_struct, int i, char *oldtex);
t_fillmap			ft_fullfill_map_varset(void);
int					open_window(char **mapcub, int count_line, t_tex *tex,
					t_map *map_struct);
void				init_background(t_renderer *rdr);
t_renderer			*init_rdr(int width, int height, int color_floor,
					unsigned int color_roof);
char				*ft_strdup(char *s1);
int					ft_cast_loop(t_ray_struct *ray_s);
t_ch				*init_ch(char **map, int line, t_map *mapstruct);
char				*ft_itoa(int n);
t_tex				*init_tex(t_tex *tex, t_renderer *rdr);
int					ft_move(t_ray_struct *ray_s);
void				ft_turn(t_ray_struct *ray_s, int speed);
int					key_released(int kay, t_ray_struct *ray_s);
int					key_pressed(int key, t_ray_struct *ray_s);
int					ft_set_speed(t_ray_struct *ray_s);
unsigned int		*back_color(unsigned int color_floor,
					unsigned int color_roof, int deg_power);
char				*ft_strdup(char *s1);
t_ray_hit			ft_hori(char **map, t_ray_struct *ray_s, float angle);
t_ray_hit			ft_vert(char **map, t_ray_struct *ray_s, float angle);
t_darken			set_darkness(unsigned int tex_col, float dark_r);
void				ft_draw_wall_e(t_ray_struct *ray_s, double wall_size,
					int col, t_ray_hit hit_info);
void				ft_draw_wall_w(t_ray_struct *ray_s, double wall_size,
					int col, t_ray_hit hit_info);
void				ft_draw_wall_n(t_ray_struct *ray_s, double wall_size,
					int col, t_ray_hit hit_info);
void				ft_draw_wall_s(t_ray_struct *ray_s, double wall_size,
					int col, t_ray_hit hit_info);
void				init_sprite(t_sprite_info *sprite, t_renderer *rdr,
					t_map *map_struct);
t_sprite			*init_sprite_list(char **map, int line,
					t_ray_struct *ray_s);
void				ft_sprite(t_ray_struct *ray_s);
void				ft_sorder(t_ray_struct *ray_s);
void				ft_slocate(t_ray_struct *ray_s, double dirx,
					double diry, double dist);
void				ft_sdraw(t_ray_struct *ray_s, int loc, double dist);
void				ft_sdraw_close(t_ray_struct *ray_s, int loc, double dist);
void				ft_sdraw_mid(t_ray_struct *ray_s, int loc, double dist);
void				ft_sdraw_midf(t_ray_struct *ray_s, int loc, double dist);
unsigned int		ft_spixel_low(t_ray_struct *ray_s, int index,
					unsigned int col);
int					print_image(t_renderer *rdr, t_ch *ch);
int					exit_program(t_ray_struct *ray_s);
char				*ft_set_tex(t_map *map_struct, int i, char *oldtex);
int					ft_test(t_map *map_struct, int i, int j);
#endif
