/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lod_far.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:12:50 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/04 12:39:51 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3d.h"
#include "../../../includes/get_next_line.h"

unsigned int	ft_spixel(t_ray_struct *ray_s, int index, unsigned int col)
{
	int	t;
	int	r;
	int	g;
	int	b;

	if (col >= NONE)
		return (ray_s->rdr->img_data[index]);
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

void			ft_sdraw_far_a(t_ray_struct *ray_s, t_sdraw s,
				double dist, int loc)
{
	t_darken ratio;

	if (ray_s->rdr->sprites_info->texa[ray_s->rdr->sprites_info->frame][s.cl]
		< NONE)
	{
		ratio = set_darkness(ray_s->rdr->sprites_info->texa
			[ray_s->rdr->sprites_info->frame][s.cl], DARKNESS / dist);
		s.cl = ratio.r * 0x010000
		+ ratio.g * 0x0100 + ratio.b;
	}
	else
		s.cl = NONE;
	s.index = loc + s.i + (s.j + ray_s->view_h - 1) * ray_s->rdr->r_wid;
	if (s.index < ray_s->rdr->r_size && s.index >= 0)
		ray_s->rdr->img_data[s.index] = ft_spixel(ray_s, s.index, s.cl);
}

void			ft_sdraw_2(t_ray_struct *ray_s, t_sdraw s, double d, int loc)
{
	t_darken		ratio;

	s.cl = ray_s->rdr->sprites_info->tex_w *
	floor(ray_s->rdr->sprites_info->tex_h * (double)s.j / s.size) + (double)s.i
	/ s.size * ray_s->rdr->sprites_info->tex_w;
	if (ray_s->rdr->sprites_info->isa == 1)
		ft_sdraw_far_a(ray_s, s, d, loc);
	else
	{
		if (ray_s->rdr->sprites_info->tex[s.cl] < NONE)
		{
			ratio = set_darkness(ray_s->rdr->sprites_info->tex[s.cl],
					DARKNESS / d);
			s.cl = ratio.r * 0x010000
			+ ratio.g * 0x0100 + ratio.b;
		}
		else
			s.cl = NONE;
		s.index = loc + s.i + (s.j + ray_s->view_h - 1) * ray_s->rdr->r_wid;
		if (s.index < ray_s->rdr->r_size && s.index >= 0)
			ray_s->rdr->img_data[s.index] = ft_spixel(ray_s, s.index, s.cl);
	}
}

void			ft_sdraw(t_ray_struct *ray_s, int loc, double dist)
{
	t_sdraw			s;

	s.i = 0;
	s.j = 0;
	s.size = ray_s->rdr->r_wid / (dist / 32);
	loc = loc - s.size / 2;
	while (s.i < s.size)
	{
		if (loc + s.i >= 0 && loc + s.i <= ray_s->rdr->r_wid - 1)
		{
			if (dist - 64 < ray_s->disttab[loc + s.i])
			{
				while (loc + s.i >= 0 && loc + s.i < ray_s->rdr->r_wid &&
					s.j < s.size)
				{
					ft_sdraw_2(ray_s, s, dist, loc);
					s.j++;
				}
				s.j = 0;
			}
		}
		s.i++;
	}
}
