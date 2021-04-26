/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_ch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 10:45:37 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/03 14:36:19 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_ch		*set_ch_var(unsigned int y, unsigned int x, float angle)
{
	t_ch	*result;

	if ((result = wrmalloc(sizeof(t_ch))) == NULL)
		return (NULL);
	result->tilex = x;
	result->tiley = y;
	result->posx = MAP_RES * x + MAP_RES / 2;
	result->posx_64 = (int)result->posx / MAP_RES;
	result->posy = MAP_RES * y + MAP_RES / 2;
	result->posy_64 = (int)result->posy / MAP_RES;
	result->angle_rad = angle;
	result->fov_rad = (FOV * M_PI) / 180;
	return (result);
}

t_ch		*init_ch_ori(char **map, int i, int j, t_ch *ch)
{
	if (map[i][j] == 'N')
		ch = set_ch_var(i, j, M_PI_2);
	else if (map[i][j] == 'E')
		ch = set_ch_var(i, j, M_PI * 2);
	else if (map[i][j] == 'S')
		ch = set_ch_var(i, j, M_PI_2 * 3);
	else if (map[i][j] == 'W')
		ch = set_ch_var(i, j, M_PI);
	return (ch);
}

void		init_frame(t_map *map_struct, t_ch *ch, int line)
{
	ch->mapline = line - 1;
	ch->speed = MAP_RES / (20000 / (map_struct->res_x + 310));
	ch->save = map_struct->save;
	if (ch->save == 1)
		ch->argu = 1;
	else
		ch->argu = 0;
	ch->frame = map_struct->frame;
	ch->delay = map_struct->delay;
}

t_ch		*init_ch(char **map, int line, t_map *map_struct)
{
	t_ch			*ch;
	int				i;
	unsigned int	j;

	i = 0;
	j = 0;
	ch = NULL;
	while (i < line)
	{
		while (map[i][j] != '\n')
		{
			ch = init_ch_ori(map, i, j, ch);
			j++;
		}
		if (ch != NULL && j != 0)
			ch->mapcol = j;
		i++;
		j = 0;
	}
	if (ch == NULL)
		ft_parse_error(NOCH);
	init_frame(map_struct, ch, line);
	return (ch);
}
