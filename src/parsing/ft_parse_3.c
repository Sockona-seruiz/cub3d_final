/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:26:28 by seruiz            #+#    #+#             */
/*   Updated: 2021/01/29 13:47:17 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"

void			ft_bzero_struct(t_map *map_struct)
{
	map_struct->save = 0;
	map_struct->frame = 0;
	map_struct->delay = 0;
	map_struct->res_x = -1;
	map_struct->res_y = -1;
	map_struct->map = NULL;
	map_struct->tex_n = NULL;
	map_struct->tex_e = NULL;
	map_struct->tex_s = NULL;
	map_struct->tex_w = NULL;
	map_struct->sprt = NULL;
	map_struct->sprta = NULL;
	map_struct->issprta = 0;
	map_struct->floor = -1;
	map_struct->roof = -1;
}

unsigned int	creatergb(int r, int g, int b)
{
	return ((r & 0xfe) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int				ft_atoi(const char *str)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (48 > str[i] || str[i] > 57)
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (-1);
		i++;
	}
	while (48 <= str[i] && str[i] <= 57)
	{
		result = (str[i] - 48) + (result * 10);
		i++;
	}
	return (result);
}

void			ft_set_res(t_map *map_struct, int i)
{
	int	j;

	j = 0;
	if (map_struct->res_x != -1 && map_struct->res_y != -1)
		ft_parse_error(RESERR);
	map_struct->res_x = ft_atoi(&map_struct->file[i][j]);
	while (48 > map_struct->file[i][j] || map_struct->file[i][j] > 57)
		j++;
	while (48 <= map_struct->file[i][j] && map_struct->file[i][j] <= 57)
		j++;
	if (map_struct->res_x > MAX_X)
		map_struct->res_x = MAX_X;
	else if (map_struct->res_x < MIN_RES)
		map_struct->res_x = MIN_RES;
	map_struct->res_y = ft_atoi(&map_struct->file[i][j]);
	if (map_struct->res_y > MAX_Y)
		map_struct->res_y = MAX_Y;
	else if (map_struct->res_y < MIN_RES)
		map_struct->res_y = MIN_RES;
}

t_fillmap		ft_fullfill_map_varset(void)
{
	t_fillmap	f;

	f.changed = 1;
	f.i = 0;
	f.j = 0;
	return (f);
}
