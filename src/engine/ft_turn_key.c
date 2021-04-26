/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_turn_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:05:41 by seruiz            #+#    #+#             */
/*   Updated: 2021/01/28 14:00:21 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		ft_turn(t_ray_struct *ray_s, int speed)
{
	if (ray_s->keys->left == 1)
	{
		if (ray_s->ch->angle_rad + (ray_s->ray_step_rad * 10 * speed)
			> M_PI * 2)
			ray_s->ch->angle_rad = ray_s->ch->angle_rad -
			(M_PI * 2) + ray_s->ray_step_rad * 10 * speed;
		else
			ray_s->ch->angle_rad += ray_s->ray_step_rad * 10 * speed;
	}
	if (ray_s->keys->right == 1)
	{
		if (ray_s->ch->angle_rad - (ray_s->ray_step_rad * 10 * speed) < 0)
			ray_s->ch->angle_rad = ray_s->ch->angle_rad + (M_PI * 2) -
			ray_s->ray_step_rad * 10 * speed;
		else
			ray_s->ch->angle_rad -= ray_s->ray_step_rad * 10 * speed;
	}
}

int			ft_set_speed(t_ray_struct *ray_s)
{
	int	speed;

	if (ray_s->keys->shift == 1)
		speed = ray_s->ch->speed * 3;
	else if (ray_s->keys->alt == 1)
		speed = ray_s->ch->speed * 0.5;
	else
		speed = ray_s->ch->speed;
	return (speed);
}

int			key_released(int key, t_ray_struct *ray_s)
{
	if (key == W)
		ray_s->keys->w = 0;
	else if (key == A)
		ray_s->keys->a = 0;
	else if (key == S)
		ray_s->keys->s = 0;
	else if (key == D)
		ray_s->keys->d = 0;
	else if (key == LEFT)
		ray_s->keys->left = 0;
	else if (key == RIGHT)
		ray_s->keys->right = 0;
	else if (key == SHIFT)
		ray_s->keys->shift = 0;
	else if (key == ALT)
		ray_s->keys->alt = 0;
	else if (key == UP)
		ray_s->keys->up = 0;
	else if (key == DOWN)
		ray_s->keys->down = 0;
	return (1);
}

int			key_pressed(int key, t_ray_struct *ray_s)
{
	if (key == F12)
		ray_s->ch->save = 1;
	else if (key == W)
		ray_s->keys->w = 1;
	else if (key == A)
		ray_s->keys->a = 1;
	else if (key == S)
		ray_s->keys->s = 1;
	else if (key == D)
		ray_s->keys->d = 1;
	else if (key == LEFT)
		ray_s->keys->left = 1;
	else if (key == RIGHT)
		ray_s->keys->right = 1;
	else if (key == SHIFT)
		ray_s->keys->shift = 1;
	else if (key == UP)
		ray_s->keys->up = 1;
	else if (key == DOWN)
		ray_s->keys->down = 1;
	else if (key == ALT)
		ray_s->keys->alt = 1;
	else if (key == ESC)
		ft_parse_error(NOERROR);
	return (1);
}
