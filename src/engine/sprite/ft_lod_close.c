/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lod_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:16:59 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/04 12:39:35 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3d.h"
#include "../../../includes/get_next_line.h"

unsigned int	ft_spixel_low(t_ray_struct *ray_s, int index, unsigned int col)
{
	int	t;
	int	r;
	int	g;
	int	b;

	if (col >= NONE)
		return (0);
	if (col < 256 * 256 * 256)
		return (col);
	t = col / (256 * 256 * 256);
	r = (col / (256 * 256) % 256) * (1 - (double)t / 256);
	g = (col / 256 % 256) * (1 - (double)t / 256);
	b = (col % 256) * (1 - (double)t / 256);
	r += (ray_s->rdr->img_data[index] / (256 * 256) % 256) * ((double)t / 256);
	g += (ray_s->rdr->img_data[index] / 256 % 256) * ((double)t / 256);
	b += (ray_s->rdr->img_data[index] % 256) * ((double)t / 256);
	return (r * 256 * 256 + g * 256 + b);
}

void			ft_fill_holes_low(t_ray_struct *ray_s, t_sdraw s,
				unsigned int col)
{
	ray_s->rdr->img_data[s.index] = col;
	ray_s->rdr->img_data[s.index + 1] = col;
	ray_s->rdr->img_data[s.index + 2] = col;
	ray_s->rdr->img_data[s.index + 3] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid + 1] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid + 2] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid + 3] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 2] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 2 + 1] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 2 + 2] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 2 + 3] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 3] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 3 + 1] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 3 + 2] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 3 + 3] = col;
}

void			ft_sdraw_low_a(t_ray_struct *ray_s, t_sdraw s,
				double dist, int loc)
{
	t_darken		ratio;
	unsigned int	col;

	if (ray_s->rdr->sprites_info->texa[ray_s->rdr->sprites_info->frame]
		[s.cl] < NONE)
	{
		ratio = set_darkness(ray_s->rdr->sprites_info->texa
			[ray_s->rdr->sprites_info->frame][s.cl], DARKNESS / dist);
		s.cl = ratio.r * 0x010000
		+ ratio.g * 0x0100 + ratio.b;
	}
	else
		s.cl = NONE;
	s.index = loc + s.i + (s.j + ray_s->view_h - 1) * ray_s->rdr->r_wid;
	if (s.index < ray_s->rdr->r_size && s.index >= 0 &&
		s.index + ray_s->rdr->r_wid * 3 + 3 < ray_s->rdr->r_size)
	{
		if ((col = ft_spixel_low(ray_s, s.index, s.cl)) == 0)
			return ;
		ft_fill_holes_low(ray_s, s, col);
	}
}

void			ft_sdraw_2_low(t_ray_struct *ray_s, t_sdraw s,
				double d, int loc)
{
	t_darken		r;
	unsigned int	col;

	s.cl = ray_s->rdr->sprites_info->tex_w *
	floor(ray_s->rdr->sprites_info->tex_h * (double)s.j / s.size) + (double)s.i
	/ s.size * ray_s->rdr->sprites_info->tex_w;
	if (ray_s->rdr->sprites_info->isa == 1)
		ft_sdraw_low_a(ray_s, s, d, loc);
	else
	{
		if (ray_s->rdr->sprites_info->tex[s.cl] < NONE)
		{
			r = set_darkness(ray_s->rdr->sprites_info->tex[s.cl], DARKNESS / d);
			s.cl = r.r * 0x010000 + r.g * 0x0100 + r.b;
		}
		else
			s.cl = NONE;
		s.index = loc + s.i + (s.j + ray_s->view_h - 1) * ray_s->rdr->r_wid;
		if (s.index < ray_s->rdr->r_size && s.index >= 0 &&
			s.index + ray_s->rdr->r_wid * 3 + 3 < ray_s->rdr->r_size)
		{
			if ((col = ft_spixel_low(ray_s, s.index, s.cl)) != 0)
				ft_fill_holes_low(ray_s, s, col);
		}
	}
}

void			ft_sdraw_close(t_ray_struct *ray_s, int loc, double dist)
{
	t_sdraw			s;

	s.i = 0;
	s.j = 0;
	s.size = ray_s->rdr->r_wid / (dist / 32);
	loc = loc - s.size / 2;
	while (s.i < s.size)
	{
		if (loc + s.i >= 0 && loc + s.i < ray_s->rdr->r_wid)
		{
			if (dist <= ray_s->disttab[loc + s.i])
			{
				while (loc + s.i >= 0 && loc + s.i < ray_s->rdr->r_wid - 4 &&
					s.j < s.size)
				{
					ft_sdraw_2_low(ray_s, s, dist, loc);
					s.j += 4;
				}
				s.j = 0;
			}
		}
		s.i += 4;
	}
}
