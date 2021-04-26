/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:44:21 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/04 11:56:30 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"

int			exit_program(t_ray_struct *ray_s)
{
	ray_s->spritenb = 0;
	wrdestroy();
	exit(0);
}

int			inf_loop(t_ray_struct *ray_s)
{
	mlx_hook(ray_s->rdr->win, 17, 0, exit_program, ray_s);
	mlx_hook(ray_s->rdr->win, 2, 1L << 0, key_pressed, ray_s);
	mlx_hook(ray_s->rdr->win, 3, 1L << 1, key_released, ray_s);
	mlx_loop_hook(ray_s->rdr->mlx_ptr, ft_move, ray_s);
	mlx_loop(ray_s->rdr->mlx_ptr);
	return (0);
}

void		ray_ssetup(t_ray_struct *ray_s, t_ch *ch, t_renderer *rdr)
{
	ray_s->rdr = rdr;
	ray_s->ch = ch;
	ray_s->view_h = rdr->r_hei / 2;
	ray_s->ray_step_rad = ch->fov_rad / (float)rdr->r_wid;
	ray_s->half_fov_rad = ch->fov_rad / 2;
	ray_s->screen_dist = (rdr->r_wid / 2) / tan(ray_s->half_fov_rad);
	ray_s->up_lim = ray_s->rdr->r_hei / 2 + (ray_s->rdr->r_hei / 2) / 2;
	ray_s->down_lim = ray_s->rdr->r_hei / 2 - (ray_s->rdr->r_hei / 2) / 2;
}

void		inf_loop_setup(t_renderer *rdr, t_ch *ch, char **map, t_tex *tex)
{
	t_ray_struct	ray_s;
	t_key			keys;
	int				i;

	keys.w = 0;
	keys.s = 0;
	keys.a = 0;
	keys.d = 0;
	keys.left = 0;
	keys.right = 0;
	keys.alt = 0;
	ray_s.keys = &keys;
	ray_s.map = map;
	ray_s.tex = tex;
	ray_ssetup(&ray_s, ch, rdr);
	ray_s.sprite_list = init_sprite_list(map, rdr->map_line, &ray_s);
	i = ray_s.spritenb;
	if ((ray_s.disttab = wrmalloc(sizeof(double) * (rdr->r_wid + 1))) == 0)
	{
		return ;
	}
	inf_loop(&ray_s);
}

int			open_window(char **map, int count_line, t_tex *tex,
			t_map *map_struct)
{
	t_renderer	*rdr;
	t_ch		*character;

	character = init_ch(map_struct->map, map_struct->mapy, map_struct);
	rdr = init_rdr(map_struct->res_x, map_struct->res_y, map_struct->floor,
	map_struct->roof);
	tex = init_tex(tex, rdr);
	rdr->map_line = count_line;
	init_sprite(map_struct->sprite, rdr, map_struct);
	inf_loop_setup(rdr, character, map, tex);
	return (0);
}
