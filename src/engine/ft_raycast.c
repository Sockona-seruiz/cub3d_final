/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:43:45 by seruiz            #+#    #+#             */
/*   Updated: 2021/01/26 15:24:06 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_darken		set_darkness(unsigned int tex_col, float dark_r)
{
	t_darken	ratio;

	ratio.r = (tex_col / 0x010000);
	ratio.r2 = ratio.r;
	ratio.g = (tex_col / 0x000100 - ratio.r * 0x0100);
	ratio.g2 = ratio.g;
	ratio.b = (tex_col - ratio.r * 0x010000 - ratio.g * 0x000100);
	ratio.b2 = ratio.b;
	if ((ratio.r = ratio.r * dark_r) > ratio.r2)
		ratio.r = ratio.r2;
	if ((ratio.g = ratio.g * dark_r) > ratio.g2)
		ratio.g = ratio.g2;
	if ((ratio.b = ratio.b * dark_r) > ratio.b2)
		ratio.b = ratio.b2;
	return (ratio);
}

void			ft_calc_wall_size_2(t_ray_struct *ray_s, float angle, int col,
		t_ray_hit hit_vert)
{
	double		wall_size;

	ray_s->hit_info = hit_vert;
	hit_vert.dist = hit_vert.dist * cosf(angle - ray_s->ch->angle_rad);
	if (hit_vert.dist == 0)
		hit_vert.dist = 1;
	ray_s->ori = hit_vert.ori;
	wall_size = (MAP_RES * ray_s->screen_dist) / hit_vert.dist;
	ray_s->disttab[col - 1] = hit_vert.dist;
	if (ray_s->ori == 'E')
		ft_draw_wall_e(ray_s, wall_size, col, hit_vert);
	else
		ft_draw_wall_w(ray_s, wall_size, col, hit_vert);
}

void			ft_calc_wall_size(t_ray_struct *ray_s, float angle, int col)
{
	double		wall_size;
	t_ray_hit	hit_hori;
	t_ray_hit	hit_vert;

	hit_hori = ft_hori(ray_s->map, ray_s, angle);
	hit_vert = ft_vert(ray_s->map, ray_s, angle);
	if (hit_hori.dist <= hit_vert.dist)
	{
		ray_s->hit_info = hit_hori;
		hit_hori.dist = hit_hori.dist * cosf(angle - ray_s->ch->angle_rad);
		if (hit_hori.dist == 0)
			hit_hori.dist = 1;
		ray_s->ori = hit_hori.ori;
		wall_size = (MAP_RES * ray_s->screen_dist) / hit_hori.dist;
		ray_s->disttab[col - 1] = hit_hori.dist;
		if (ray_s->ori == 'N')
			ft_draw_wall_n(ray_s, wall_size, col, hit_hori);
		else
			ft_draw_wall_s(ray_s, wall_size, col, hit_hori);
		return ;
	}
	ft_calc_wall_size_2(ray_s, angle, col, hit_vert);
}

int				ft_cast_loop(t_ray_struct *ray_s)
{
	float		angle_left;
	float		angle_right;
	float		angle;
	int			i;

	i = 0;
	angle_left = ray_s->ch->angle_rad + ray_s->half_fov_rad;
	angle_right = ray_s->ch->angle_rad - ray_s->half_fov_rad;
	angle = angle_left;
	while (i < ray_s->rdr->r_wid)
	{
		i++;
		ft_calc_wall_size(ray_s, angle, i);
		angle -= ray_s->ray_step_rad;
		if (angle > M_PI * 2)
			angle = angle - (M_PI * 2);
	}
	ft_sprite(ray_s);
	return (1);
}
