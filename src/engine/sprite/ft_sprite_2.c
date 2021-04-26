/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:30:01 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/04 12:29:30 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3d.h"
#include "../../../includes/get_next_line.h"

void			ft_set_frame(t_ray_struct *ray_s)
{
	ray_s->rdr->sprites_info->framebuff++;
	if (ray_s->rdr->sprites_info->framebuff >= ray_s->ch->delay)
	{
		ray_s->rdr->sprites_info->framebuff = 0;
		if (ray_s->rdr->sprites_info->frame == ray_s->ch->frame - 1)
			ray_s->rdr->sprites_info->frame = 0;
		else
			ray_s->rdr->sprites_info->frame++;
	}
}

void			ft_slocate(t_ray_struct *ray_s, double dirx,
				double diry, double dist)
{
	double	angle;

	dirx = ((dirx - ray_s->ch->posx) / dist);
	diry = ((diry - ray_s->ch->posy) / dist);
	if (diry <= 0)
		angle = acosf(dirx) * 180 / M_PI;
	else
		angle = 360 - acosf(dirx) * 180 / M_PI;
	angle = ray_s->dir - angle + 30;
	if (angle >= 180)
		angle -= 360;
	else if (angle <= -180)
		angle += 360;
	angle *= 1.1;
	if (dist < 100)
		ft_sdraw_close(ray_s, angle * ray_s->rdr->r_wid / 66, dist);
	if (dist < 800)
		ft_sdraw_midf(ray_s, (angle) * ray_s->rdr->r_wid / 66, dist);
	else if (dist < 1200)
		ft_sdraw_mid(ray_s, angle * ray_s->rdr->r_wid / 66, dist);
	else
		ft_sdraw(ray_s, angle * ray_s->rdr->r_wid / 66, dist);
}

void			ft_sorder(t_ray_struct *ray_s)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	ft_set_frame(ray_s);
	while (i < ray_s->spritenb)
	{
		j = i + 1;
		while (j < ray_s->spritenb)
		{
			if (ray_s->sprite_list[i].dist < ray_s->sprite_list[j].dist)
			{
				tmp = ray_s->sprite_list[i];
				ray_s->sprite_list[i] = ray_s->sprite_list[j];
				ray_s->sprite_list[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
