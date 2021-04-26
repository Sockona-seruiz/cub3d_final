/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:03:19 by seruiz            #+#    #+#             */
/*   Updated: 2021/01/26 15:24:06 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_ray_hit	ft_hori_2(char **map, t_ray_struct *ray_s, t_point a,
			t_ray_hit hit_info)
{
	if (a.col > ray_s->ch->mapcol || a.col < 0 ||
		a.line > ray_s->ch->mapline || a.line < 0)
	{
		hit_info.dist = LONG_MAX;
		return (hit_info);
	}
	while (map[a.line][a.col] != '1')
	{
		hit_info.hit_x += a.x;
		a.col = (hit_info.hit_x / MAP_RES);
		hit_info.hit_y += a.y;
		a.line = (hit_info.hit_y / MAP_RES);
		if (a.col > ray_s->ch->mapcol || a.col < 0 ||
			a.line > ray_s->ch->mapline || a.line < 0)
		{
			hit_info.dist = LONG_MAX;
			return (hit_info);
		}
	}
	hit_info.dist = sqrtf(((ray_s->ch->posx - hit_info.hit_x) *
	(ray_s->ch->posx - hit_info.hit_x)) + ((ray_s->ch->posy - hit_info.hit_y)
	* (ray_s->ch->posy - hit_info.hit_y)));
	hit_info.tex_off_x = hit_info.hit_x - MAP_RES * a.col;
	return (hit_info);
}

t_ray_hit	ft_hori(char **map, t_ray_struct *ray_s, float angle)
{
	t_point		a;
	t_ray_hit	hit_info;

	if (angle <= M_PI && angle > 0)
	{
		hit_info.ori = 'N';
		hit_info.hit_y = (int)(ray_s->ch->posy / MAP_RES) * MAP_RES - 0.0005;
		a.y = -MAP_RES;
		a.x = MAP_RES / tanf(angle);
	}
	else
	{
		hit_info.ori = 'S';
		hit_info.hit_y = (int)(ray_s->ch->posy / MAP_RES) * MAP_RES + MAP_RES;
		a.y = MAP_RES;
		a.x = (-MAP_RES / tanf(angle));
	}
	hit_info.hit_x = ray_s->ch->posx + ((ray_s->ch->posy - hit_info.hit_y)
			/ tanf(angle));
	a.col = (hit_info.hit_x / MAP_RES);
	a.line = (hit_info.hit_y / MAP_RES);
	return (ft_hori_2(map, ray_s, a, hit_info));
}

t_ray_hit	ft_vert_2(char **map, t_ray_struct *ray_s,
			t_point a, t_ray_hit hit_info)
{
	if (a.col > ray_s->ch->mapcol || a.col < 0 ||
		a.line > ray_s->ch->mapline || a.line < 0)
	{
		hit_info.dist = LONG_MAX;
		return (hit_info);
	}
	while (map[a.line][a.col] != '1')
	{
		hit_info.hit_x += a.x;
		a.col = hit_info.hit_x / MAP_RES;
		hit_info.hit_y += a.y;
		a.line = hit_info.hit_y / MAP_RES;
		if (a.col > ray_s->ch->mapcol || a.col < 0 ||
			a.line > ray_s->ch->mapline || a.line < 0)
		{
			hit_info.dist = LONG_MAX;
			return (hit_info);
		}
	}
	hit_info.dist = sqrtf((ray_s->ch->posx - hit_info.hit_x)
	* (ray_s->ch->posx - hit_info.hit_x) + (ray_s->ch->posy - hit_info.hit_y)
	* (ray_s->ch->posy - hit_info.hit_y));
	hit_info.tex_off_y = hit_info.hit_y - MAP_RES * a.line;
	return (hit_info);
}

t_ray_hit	ft_vert(char **map, t_ray_struct *ray_s, float angle)
{
	t_point		a;
	t_ray_hit	hit_info;

	if (angle > M_PI_2 && angle <= (M_PI_2 * 3))
	{
		hit_info.ori = 'W';
		hit_info.hit_x = (int)(ray_s->ch->posx / MAP_RES) * MAP_RES - 0.0005;
		a.x = -MAP_RES;
		a.y = (MAP_RES * tanf(angle));
	}
	else
	{
		hit_info.ori = 'E';
		hit_info.hit_x = (int)(ray_s->ch->posx / MAP_RES) * MAP_RES + MAP_RES;
		a.x = MAP_RES;
		a.y = -MAP_RES * tanf(angle);
	}
	hit_info.hit_y = (ray_s->ch->posy + ((ray_s->ch->posx - hit_info.hit_x)
				* tanf(angle)));
	a.col = hit_info.hit_x / MAP_RES;
	a.line = hit_info.hit_y / MAP_RES;
	return (ft_vert_2(map, ray_s, a, hit_info));
}
