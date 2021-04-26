/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 12:38:09 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/03 14:55:22 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/print_image.h"

float		set_angle(float ch_angle)
{
	float	angle;

	if (ch_angle - M_PI_2 < 0)
		angle = (M_PI * 2) + ch_angle - M_PI_2;
	else
		angle = ch_angle - M_PI_2;
	return (angle);
}

void		ft_move_ad(t_ray_struct *ray_s, int speed)
{
	float	angle;

	if (ray_s->keys->a == 1)
	{
		angle = set_angle(ray_s->ch->angle_rad);
		if (ray_s->map[ray_s->ch->posy_64][(int)((ray_s->ch->posx
			- cosf(angle) * speed) / MAP_RES)] != '1')
			ray_s->ch->posx -= cosf(angle) * speed;
		if (ray_s->map[(int)((ray_s->ch->posy + sinf(angle) *
			speed) / MAP_RES)][ray_s->ch->posx_64] != '1')
			ray_s->ch->posy += sinf(angle) * speed;
	}
	if (ray_s->keys->d == 1)
	{
		angle = set_angle(ray_s->ch->angle_rad);
		if (ray_s->map[ray_s->ch->posy_64][(int)((ray_s->ch->posx +
			cosf(angle) * speed) / MAP_RES)] != '1')
			ray_s->ch->posx += cosf(angle) * speed;
		if (ray_s->map[(int)((ray_s->ch->posy - sinf(angle) *
			speed) / MAP_RES)][ray_s->ch->posx_64] != '1')
			ray_s->ch->posy -= sinf(angle) * speed;
	}
}

void		ft_move_ws(t_ray_struct *ray_s, int speed)
{
	if (ray_s->keys->w == 1)
	{
		if (ray_s->map[ray_s->ch->posy_64][(int)((ray_s->ch->posx +
			cosf(ray_s->ch->angle_rad) * speed) / MAP_RES)] != '1')
			ray_s->ch->posx += cosf(ray_s->ch->angle_rad) * speed;
		if (ray_s->map[(int)((ray_s->ch->posy - sinf(ray_s->ch->angle_rad) *
			speed) / MAP_RES)][ray_s->ch->posx_64] != '1')
			ray_s->ch->posy -= sinf(ray_s->ch->angle_rad) * speed;
	}
	if (ray_s->keys->s == 1)
	{
		if (ray_s->map[ray_s->ch->posy_64][(int)((ray_s->ch->posx -
			cosf(ray_s->ch->angle_rad) * speed) / MAP_RES)] != '1')
			ray_s->ch->posx -= cosf(ray_s->ch->angle_rad) * speed;
		if (ray_s->map[(int)((ray_s->ch->posy + sinf(ray_s->ch->angle_rad) *
			speed) / MAP_RES)][ray_s->ch->posx_64] != '1')
			ray_s->ch->posy += sinf(ray_s->ch->angle_rad) * speed;
	}
	ft_move_ad(ray_s, speed);
}

void		set_head_tilt(t_ray_struct *ray_s, int speed)
{
	if (ray_s->keys->up == 1 && ray_s->view_h < ray_s->up_lim)
		ray_s->view_h += 5 * speed;
	if (ray_s->keys->down == 1 && ray_s->view_h > ray_s->down_lim)
		ray_s->view_h -= 5 * speed;
}

int			ft_move(t_ray_struct *ray_s)
{
	int			speed;
	int			i;
	int			j;

	i = 0;
	j = 0;
	ray_s->ch->posx_64 = (int)ray_s->ch->posx / MAP_RES;
	ray_s->ch->posy_64 = (int)ray_s->ch->posy / MAP_RES;
	speed = ft_set_speed(ray_s);
	ft_move_ws(ray_s, speed);
	ft_turn(ray_s, speed);
	ft_cast_loop(ray_s);
	if (ray_s->ch->save == 1)
	{
		print_image(ray_s->rdr, ray_s->ch);
		if (ray_s->ch->argu == 1)
			ft_parse_error(NOERROR);
	}
	mlx_put_image_to_window(ray_s->rdr->mlx_ptr, ray_s->rdr->win,
		ray_s->rdr->img_ptr, 0, 0);
	set_head_tilt(ray_s, speed);
	return (0);
}
