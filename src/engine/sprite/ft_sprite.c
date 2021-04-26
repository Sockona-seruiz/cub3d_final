/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:52:15 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/03 12:03:58 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3d.h"
#include "../../../includes/get_next_line.h"

void		ft_sprite(t_ray_struct *ray_s)
{
	int		i;

	if (ray_s->ch->angle_rad - (FOV / 2) <= M_PI)
		ray_s->dir = ray_s->ch->angle_rad * 180 / M_PI;
	else
		ray_s->dir = 360 - ray_s->ch->angle_rad * 180 / M_PI;
	i = 0;
	while (i < ray_s->spritenb)
	{
		ray_s->sprite_list[i].dist = hypot(ray_s->sprite_list[i].posx -
		ray_s->ch->posx, ray_s->sprite_list[i].posy - ray_s->ch->posy);
		i++;
	}
	ft_sorder(ray_s);
	i = 0;
	while (i < ray_s->spritenb)
	{
		if (ray_s->sprite_list[i].dist > 12)
			ft_slocate(ray_s, ray_s->sprite_list[i].posx,
			ray_s->sprite_list[i].posy, ray_s->sprite_list[i].dist);
		i++;
	}
}

t_sprite	*init_sprite_list_2(char **map, int line, t_sprite *list)
{
	int				count;
	int				i;
	unsigned int	j;

	count = 0;
	i = 0;
	j = 0;
	while (i < line)
	{
		while (map[i][j] != '\n')
		{
			if (map[i][j] == '2')
			{
				list[count].posx = (j + 0.5) * MAP_RES;
				list[count].posy = (i + 0.5) * MAP_RES;
				count++;
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (list);
}

t_sprite	*init_sprite_list(char **map, int line, t_ray_struct *ray_s)
{
	t_sprite		*list;
	int				count;
	int				i;
	unsigned int	j;

	count = 0;
	i = 0;
	j = 0;
	while (i < line)
	{
		while (map[i][j] != '\n')
		{
			if (map[i][j] == '2')
			{
				count++;
			}
			j++;
		}
		i++;
		j = 0;
	}
	if ((list = wrmalloc(sizeof(t_sprite) * count + 1)) == 0)
		ft_parse_error(MALLOC);
	ray_s->spritenb = count;
	return (init_sprite_list_2(map, line, list));
}

void		ft_init_sprta(t_sprite_info *sprite, t_renderer *rdr,
			t_map *map_struct)
{
	int		i;
	void	*buff;
	int		osef;

	i = 0;
	sprite->isa = 1;
	sprite->frame = 0;
	sprite->framebuff = 0;
	if ((sprite->texa = wrmalloc(sizeof(unsigned int *) *
		map_struct->frame)) == 0)
		ft_parse_error(MALLOC);
	while (i < map_struct->frame)
	{
		if ((buff = mlx_xpm_file_to_image(rdr->mlx_ptr, sprite->anim_path[i],
					&sprite->tex_w, &sprite->tex_h)) == NULL)
			ft_parse_error(IMGERR);
		sprite->texa[i] = (unsigned int *)mlx_get_data_addr(buff,
						&rdr->img.bpp, &osef, &rdr->img.endian);
		i++;
	}
	rdr->sprites_info = sprite;
}

void		init_sprite(t_sprite_info *sprite, t_renderer *rdr,
			t_map *map_struct)
{
	void	*buff;
	int		osef;

	if (sprite->path != NULL)
	{
		sprite->isa = 0;
		if ((buff = mlx_xpm_file_to_image(rdr->mlx_ptr, sprite->path,
					&sprite->tex_w, &sprite->tex_h)) == NULL)
			ft_parse_error(IMGERR);
		sprite->tex = (unsigned int *)mlx_get_data_addr(buff,
						&rdr->img.bpp, &osef, &rdr->img.endian);
		rdr->sprites_info = sprite;
	}
	else
		ft_init_sprta(sprite, rdr, map_struct);
}
