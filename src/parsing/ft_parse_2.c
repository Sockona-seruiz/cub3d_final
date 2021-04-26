/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:46:20 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/03 12:28:59 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"

void	ft_fullfill_map(t_map_file s, char **mapcpy)
{
	t_fillmap f;

	f = ft_fullfill_map_varset();
	while (mapcpy[f.i])
	{
		if (f.i > s.ln)
			f.i = 0;
		while (mapcpy[f.i][f.j] != '\n')
		{
			if (mapcpy[f.i][f.j] == 'X')
			{
				if (f.i == 0 || f.i == s.ln - 1 || f.j == 0 || f.j == s.max - 1)
					ft_parse_error(NOTCLOSED);
				f.changed = ft_replace_x(s, mapcpy, f.i, f.j);
				if (f.changed == 1)
				{
					f.i = 0;
					f.j = -1;
				}
			}
			f.j++;
		}
		f.j = 0;
		f.i++;
	}
}

void	ft_cpy_map_2(int i, int j, char **mapcpy, t_map *map_struct)
{
	mapcpy[i][j] = map_struct->map[i][j];
	if (mapcpy[i][j] == 'N' || mapcpy[i][j] == 'E' ||
		mapcpy[i][j] == 'W' || mapcpy[i][j] == 'S')
		mapcpy[i][j] = 'X';
}

void	ft_cpy_map(t_map *map_struct, t_map_file s)
{
	int		i;
	int		j;
	char	**mapcpy;

	i = 0;
	j = 0;
	if ((mapcpy = wrmalloc(sizeof(char *) * (s.ln + 1))) == 0)
		ft_parse_error(MALLOC);
	mapcpy[s.ln] = 0;
	while (i < s.ln)
	{
		if ((mapcpy[i] = wrmalloc(sizeof(char) * (s.max + 1))) == 0)
			ft_parse_error(MALLOC);
		mapcpy[i][s.max] = '\n';
		while (j < s.max)
		{
			ft_cpy_map_2(i, j, mapcpy, map_struct);
			j++;
		}
		j = 0;
		i++;
	}
	ft_fullfill_map(s, mapcpy);
	wrfree(mapcpy);
}

void	ft_is_closed_2(t_map *map_struct, int i, int j)
{
	if (map_struct->map[i][j] != '1' && map_struct->map[i][j] != '0' &&
		map_struct->map[i][j] != '2' && map_struct->map[i][j] != 'N' &&
		map_struct->map[i][j] != 'E' && map_struct->map[i][j] != 'S' &&
		map_struct->map[i][j] != 'W' && map_struct->map[i][j] != '\n')
		ft_parse_error(WRGCHARAC);
}

void	ft_is_closed(t_map *map_struct, t_map_file s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map_struct->map[i])
	{
		while (map_struct->map[i][j + 1] != '\n')
		{
			ft_is_closed_2(map_struct, i, j);
			if (map_struct->map[i][j] == 'N' || map_struct->map[i][j] == 'E' ||
			map_struct->map[i][j] == 'S' || map_struct->map[i][j] == 'W')
			{
				if (s.pos_found == 1)
					ft_parse_error(MULTICH);
				s.pos_found = 1;
			}
			j++;
		}
		i++;
		j = 0;
	}
	ft_cpy_map(map_struct, s);
}
