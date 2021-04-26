/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lod_mid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:13:16 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/04 12:39:47 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3d.h"
#include "../../../includes/get_next_line.h"

void			ft_fill_holes_mid(t_ray_struct *ray_s, t_sdraw s,
				unsigned int col)
{
	ray_s->rdr->img_data[s.index] = col;
	ray_s->rdr->img_data[s.index + 1] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid + 1] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 2] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 2 + 1] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 3] = col;
	ray_s->rdr->img_data[s.index + ray_s->rdr->r_wid * 3 + 1] = col;
}

void			ft_sdraw_mid_a(t_ray_struct *ray_s, t_sdraw s,
				double dist, int loc)
{
	t_darken		ratio;
	unsigned int	col;

	if (ray_s->rdr->sprites_info->texa[ray_s->rdr->sprites_info->frame]
		[s.cl] < NONE)
	{
		ratio = set_darkness(ray_s->rdr->sprites_info->texa
			[ray_s->rdr->sprites_info->frame][s.cl], DARKNESS / dist);
		s.cl = ratio.r * 0x010000 + ratio.g * 0x0100 + ratio.b;
	}
	else
		s.cl = NONE;
	s.index = loc + s.i + (s.j + ray_s->view_h - 1) * ray_s->rdr->r_wid;
	if (s.index < ray_s->rdr->r_size && s.index >= 0 &&
		s.index + ray_s->rdr->r_wid * 3 + 1 < ray_s->rdr->r_size)
	{
		if ((col = ft_spixel_low(ray_s, s.index, s.cl)) != 0)
			ft_fill_holes_mid(ray_s, s, col);
	}
}

void			ft_sdraw_2_mid(t_ray_struct *ray_s, t_sdraw s,
				double d, int loc)
{
	t_darken		r;
	unsigned int	col;

	s.cl = ray_s->rdr->sprites_info->tex_w *
	floor(ray_s->rdr->sprites_info->tex_h * (double)s.j / s.size) + (double)s.i
	/ s.size * ray_s->rdr->sprites_info->tex_w;
	if (ray_s->rdr->sprites_info->isa == 1)
		ft_sdraw_mid_a(ray_s, s, d, loc);
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
			s.index + ray_s->rdr->r_wid * 3 + 1 < ray_s->rdr->r_size)
		{
			if ((col = ft_spixel_low(ray_s, s.index, s.cl)) != 0)
				ft_fill_holes_mid(ray_s, s, col);
		}
	}
}

void			ft_sdraw_mid(t_ray_struct *ray_s, int loc, double dist)
{
	t_sdraw			s;

	s.i = 0;
	s.j = 0;
	s.size = ray_s->rdr->r_wid / (dist / 32);
	loc = loc - s.size / 2;
	while (s.i < s.size)
	{
		if (loc + s.i >= 0 && loc + s.i <= ray_s->rdr->r_wid - 2)
		{
			if (dist - 64 < ray_s->disttab[loc + s.i])
			{
				while (loc + s.i >= 0 && loc + s.i < ray_s->rdr->r_wid &&
					s.j < s.size)
				{
					ft_sdraw_2_mid(ray_s, s, dist, loc);
					s.j += 2;
				}
				s.j = 0;
			}
		}
		s.i += 2;
	}
}
