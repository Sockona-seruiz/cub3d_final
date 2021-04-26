/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:39:36 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/03 12:16:15 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"

void	ft_paste_map(t_map *map_struct, int i, t_map_file s)
{
	s.j = 0;
	s.y = 0;
	s.pos_found = 0;
	while (map_struct->file[i])
	{
		if ((int)ft_strlen(map_struct->file[i]) > 0)
		{
			if (!(map_struct->map[s.ln] = wrmalloc(sizeof(char) * s.max + 1)))
				ft_parse_error(MALLOC);
			while (s.y < s.max)
			{
				if (s.y < (int)ft_strlen(map_struct->file[i]) &&
					map_struct->file[i][s.y] != ' ')
					map_struct->map[s.ln][s.y] = map_struct->file[i][s.y];
				else
					map_struct->map[s.ln][s.y] = '0';
				s.y++;
			}
			map_struct->map[s.ln][s.y] = '\n';
			s.y = 0;
			s.ln++;
		}
		i++;
	}
	ft_is_closed(map_struct, s);
}

void	ft_map_from_file(t_map *map_struct, int i)
{
	t_map_file	s;

	s.x = 0;
	s.y = 0;
	s.j = 0;
	s.max = 0;
	s.ln = 0;
	while (map_struct->file[i + s.j])
	{
		while (map_struct->file[i + s.j][s.y])
			s.y++;
		if (s.y > s.max)
			s.max = s.y;
		if ((int)ft_strlen(map_struct->file[i + s.j]) > 0)
			s.ln++;
		s.j++;
		s.y = 0;
	}
	map_struct->mapx = s.max;
	map_struct->mapy = s.ln;
	if (!(map_struct->map = wrmalloc(sizeof(char *) * (s.ln + 1))))
		ft_parse_error(MALLOC);
	map_struct->map[s.ln] = 0;
	s.ln = 0;
	ft_paste_map(map_struct, i, s);
}

int		ft_all_done(t_map *map_struct)
{
	if (map_struct->res_x != -1 && map_struct->res_y != -1 &&
	map_struct->tex_n != NULL && map_struct->tex_e != NULL &&
	map_struct->tex_s != NULL && map_struct->tex_w != NULL &&
	(map_struct->sprt != NULL || map_struct->sprta != NULL) &&
	map_struct->floor != -1 && map_struct->roof != -1)
		return (1);
	else
		return (0);
}

int		ft_parse_inf_2(t_map *map_struct, int i)
{
	if (map_struct->file[i][0] == 'R')
		ft_set_res(map_struct, i);
	else if (map_struct->file[i][0] == 'N' && map_struct->file[i][1] == 'O')
		map_struct->tex_n = ft_set_tex(map_struct, i, map_struct->tex_n);
	else if (map_struct->file[i][0] == 'S' && map_struct->file[i][1] == 'O')
		map_struct->tex_s = ft_set_tex(map_struct, i, map_struct->tex_s);
	else if (map_struct->file[i][0] == 'W' && map_struct->file[i][1] == 'E')
		map_struct->tex_w = ft_set_tex(map_struct, i, map_struct->tex_w);
	else if (map_struct->file[i][0] == 'E' && map_struct->file[i][1] == 'A')
		map_struct->tex_e = ft_set_tex(map_struct, i, map_struct->tex_e);
	else if (map_struct->file[i][0] == 'S' && map_struct->file[i][1] == 'A')
		map_struct->sprta = ft_set_tex_sa(map_struct, i, map_struct->sprta);
	else if (map_struct->file[i][0] == 'S')
		map_struct->sprt = ft_set_tex(map_struct, i, map_struct->sprt);
	else if (map_struct->file[i][0] == 'F')
		ft_set_floor(map_struct, i);
	else if (map_struct->file[i][0] == 'C')
		ft_set_roof(map_struct, i);
	else if (ft_all_done(map_struct) == 1)
	{
		ft_map_from_file(map_struct, i);
		return (1);
	}
	return (0);
}

void	ft_parse_inf(t_map *map_struct)
{
	int	i;

	i = 0;
	while (map_struct->file[i])
	{
		if (ft_parse_inf_2(map_struct, i) == 1)
			break ;
		i++;
	}
	if (ft_all_done(map_struct) == 0)
		ft_parse_error(MISSINFO);
}
