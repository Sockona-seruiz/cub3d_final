/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:17:31 by seruiz            #+#    #+#             */
/*   Updated: 2021/01/26 15:24:06 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	ft_draw_w_s_d_2(t_draw_w_var v, t_ray_struct *ray_s,
		int pixel, float shadow)
{
	t_darken	ratio;

	while (pixel >= v.ydown)
	{
		ratio = set_darkness(ray_s->rdr->color_tab[0], shadow);
		ray_s->rdr->img_data[pixel] = ratio.r * 0x010000
			+ ratio.g * 0x0100 + ratio.b;
		pixel -= ray_s->rdr->r_wid;
		if (shadow > 0.05)
			shadow -= 0.005;
	}
}

void	ft_draw_wall_s_down(t_draw_w_var v, t_ray_struct *ray_s,
	t_ray_hit hit_info, int col)
{
	t_darken	ratio;
	float		shadow;
	int			pixel;

	shadow = 1;
	pixel = ray_s->rdr->r_wid * ray_s->rdr->r_hei - ray_s->rdr->r_wid + col - 1;
	while (v.half > 0)
	{
		v.new_line = (int)(v.line * v.j);
		v.new_line = (ray_s->tex->south_w - v.x - 1)
			+ ray_s->tex->south_w * v.new_line;
		if (v.ydown > ray_s->rdr->wid_len)
			break ;
		if (v.new_line > ray_s->tex->south_len)
			v.new_line = ray_s->tex->south_len - 1;
		ratio = set_darkness(ray_s->tex->tex_s[v.new_line], hit_info.dark_r);
		if (v.ydown >= 0)
			ray_s->rdr->img_data[v.ydown] = ratio.r * 0x010000
				+ ratio.g * 0x0100 + ratio.b;
		v.ydown = v.ydown + ray_s->rdr->r_wid;
		v.j++;
		v.half--;
	}
	ft_draw_w_s_d_2(v, ray_s, pixel, shadow);
}

void	ft_draw_w_s_u_2(t_draw_w_var v, t_ray_struct *ray_s,
		int pixel, float shadow)
{
	t_darken ratio;

	while (pixel <= v.yup)
	{
		ratio = set_darkness(ray_s->rdr->color_tab[1], shadow);
		ray_s->rdr->img_data[pixel] = ratio.r * 0x010000
			+ ratio.g * 0x0100 + ratio.b;
		pixel += ray_s->rdr->r_wid;
		if (shadow > 0.05)
			shadow -= 0.005;
	}
}

void	ft_draw_wall_s_up(t_draw_w_var v, t_ray_struct *ray_s,
	t_ray_hit hit_info, int col)
{
	t_darken	ratio;
	float		shadow;
	int			pixel;

	shadow = 1;
	pixel = col - 1;
	while (v.i <= v.half)
	{
		v.new_line = (int)(v.line * v.j);
		v.new_line = (ray_s->tex->south_w - v.x - 1)
			+ ray_s->tex->south_w * v.new_line;
		if (v.yup < 0)
			break ;
		ratio = set_darkness(ray_s->tex->tex_s[v.new_line], hit_info.dark_r);
		if (v.yup < ray_s->rdr->r_size)
			ray_s->rdr->img_data[v.yup] = ratio.r * 0x010000
				+ ratio.g * 0x0100 + ratio.b;
		v.yup = v.yup - ray_s->rdr->r_wid;
		v.i++;
		v.j--;
	}
	ft_draw_w_s_u_2(v, ray_s, pixel, shadow);
	v.j = v.wall_size_2;
	ft_draw_wall_s_down(v, ray_s, hit_info, col);
}

void	ft_draw_wall_s(t_ray_struct *ray_s, double wall_size,
	int col, t_ray_hit hit_info)
{
	t_draw_w_var	v;

	hit_info.dark_r = (DARKNESS / hit_info.dist);
	v.line = ray_s->tex->south_h / wall_size;
	v.x = hit_info.tex_off_x * ray_s->tex->w_r_tex_s;
	v.half = wall_size * 0.5;
	v.yup = ray_s->rdr->r_wid * (ray_s->view_h) - 1 + col;
	v.ydown = v.yup;
	v.wall_size_2 = wall_size * 0.5;
	v.j = v.wall_size_2;
	v.i = 0;
	ft_draw_wall_s_up(v, ray_s, hit_info, col);
}
