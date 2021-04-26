/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:41:28 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/04 12:09:24 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"

/*
**	sprite def format : SA  (int)frames (int)delay (char *)path.xpm
*/

int			ft_test(t_map *map_struct, int i, int j)
{
	int len;

	len = 0;
	while (map_struct->file[i][j + len + 3])
	{
		if (map_struct->file[i][j + len] == '.'
		&& map_struct->file[i][j + len + 1] == 'x' &&
		map_struct->file[i][j + len + 2] == 'p' &&
		map_struct->file[i][j + len + 3] == 'm')
			break ;
		len++;
	}
	len += 4;
	return (len);
}

int			ft_change_path(char *path, int index)
{
	int i;

	i = 0;
	while (path[i + 3])
	{
		if (path[i] == '.'
		&& path[i + 1] == 'x' &&
		path[i + 2] == 'p' &&
		path[i + 3] == 'm')
		{
			if (index <= 9)
				path[i - 1] = index + 48;
			else
			{
				path[i - 1] = index - ((index / 10) * 10) + 48;
				path[i - 2] = (index / 10) + 48;
			}
			break ;
		}
		i++;
	}
	return (0);
}

int			ft_set_frame_ammount(int i, int j, t_map *map_struct, char **oldtex)
{
	int x;

	x = j;
	while (48 > map_struct->file[i][x] || map_struct->file[i][x] > 57)
		x++;
	map_struct->frame = ft_atoi(&map_struct->file[i][x]);
	while (48 <= map_struct->file[i][x] && map_struct->file[i][x] <= 57)
		x++;
	while (48 > map_struct->file[i][x] || map_struct->file[i][x] > 57)
		x++;
	map_struct->delay = ft_atoi(&map_struct->file[i][x]);
	while (48 <= map_struct->file[i][x] && map_struct->file[i][x] <= 57)
		x++;
	if (oldtex != NULL)
		ft_parse_error(MULTITEX);
	return (x);
}

t_sa		set_sa_struct(int i, int j, t_map *map_struct, char **oldtex)
{
	t_sa	s;

	s.index = 0;
	s.j = j;
	s.len_2 = 0;
	s.j = ft_set_frame_ammount(i, s.j, map_struct, oldtex);
	return (s);
}

char		**ft_set_tex_sa(t_map *map_struct, int i, char **oldtex)
{
	t_sa	s;
	char	**list;

	map_struct->issprta = 1;
	s = set_sa_struct(i, 0, map_struct, oldtex);
	if (!(list = wrmalloc((map_struct->frame) * (sizeof(char *)))))
		ft_parse_error(MALLOC);
	list[map_struct->frame - 1] = NULL;
	while (map_struct->file[i][s.j] != '.')
		s.j++;
	s.len = ft_test(map_struct, i, s.j);
	while (s.index < map_struct->frame)
	{
		if (!(list[s.index] = wrmalloc((s.len + 1) * (sizeof(char)))))
			ft_parse_error(MALLOC);
		while (s.len_2 <= s.len)
		{
			list[s.index][s.len_2] = map_struct->file[i][s.j + s.len_2];
			s.len_2++;
		}
		list[0][s.len] = '\0';
		s.len_2 = ft_change_path(list[s.index], s.index);
		s.index++;
	}
	return (list);
}
