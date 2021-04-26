/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:28:35 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/04 12:09:16 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"

void		ft_set_roof(t_map *map_struct, int i)
{
	t_col	c;

	c.j = 0;
	c.r = -1;
	c.g = -1;
	c.b = -1;
	if (map_struct->roof != -1)
		ft_parse_error(ROOFERR);
	if ((c.r = ft_atoi(&map_struct->file[i][c.j])) == -1)
		ft_parse_error(ROOFMISS);
	while (48 > map_struct->file[i][c.j] || map_struct->file[i][c.j] > 57)
		c.j++;
	while (48 <= map_struct->file[i][c.j] && map_struct->file[i][c.j] <= 57)
		c.j++;
	if ((c.g = ft_atoi(&map_struct->file[i][c.j])) == -1)
		ft_parse_error(ROOFMISS);
	while (48 > map_struct->file[i][c.j] || map_struct->file[i][c.j] > 57)
		c.j++;
	while (48 <= map_struct->file[i][c.j] && map_struct->file[i][c.j] <= 57)
		c.j++;
	if ((c.b = ft_atoi(&map_struct->file[i][c.j])) == -1)
		ft_parse_error(ROOFMISS);
	if (c.r > 255 || c.r < 0 || c.g > 255 || c.r < 0 || c.b > 255 || c.b < 0)
		ft_parse_error(OORCOLOR);
	map_struct->roof = creatergb(c.r, c.g, c.b);
}

void		ft_set_floor(t_map *map_struct, int i)
{
	t_col	c;

	c.r = -1;
	c.g = -1;
	c.b = -1;
	c.j = 0;
	if (map_struct->floor != -1)
		ft_parse_error(FLOORERR);
	if ((c.r = ft_atoi(&map_struct->file[i][c.j])) == -1)
		ft_parse_error(FLOORMISS);
	while (48 > map_struct->file[i][c.j] || map_struct->file[i][c.j] > 57)
		c.j++;
	while (48 <= map_struct->file[i][c.j] && map_struct->file[i][c.j] <= 57)
		c.j++;
	if ((c.g = ft_atoi(&map_struct->file[i][c.j])) == -1)
		ft_parse_error(FLOORMISS);
	while (48 > map_struct->file[i][c.j] || map_struct->file[i][c.j] > 57)
		c.j++;
	while (48 <= map_struct->file[i][c.j] && map_struct->file[i][c.j] <= 57)
		c.j++;
	if ((c.b = ft_atoi(&map_struct->file[i][c.j])) == -1)
		ft_parse_error(FLOORMISS);
	if (c.r > 255 || c.r < 0 || c.g > 255 || c.r < 0 || c.b > 255 || c.b < 0)
		ft_parse_error(OORCOLOR);
	map_struct->floor = creatergb(c.r, c.g, c.b);
}

int			ft_replace_x(t_map_file s, char **map, int i, int j)
{
	int	changed;

	changed = 0;
	if (i + 1 < s.ln && (map[i + 1][j] == '0' || map[i + 1][j] == '2'))
	{
		changed = 1;
		map[i + 1][j] = 'X';
	}
	if (i - 1 >= 0 && (map[i - 1][j] == '0' || map[i - 1][j] == '2'))
	{
		changed = 1;
		map[i - 1][j] = 'X';
	}
	if (j + 1 <= s.max && (map[i][j + 1] == '0' || map[i][j + 1] == '2'))
	{
		changed = 1;
		map[i][j + 1] = 'X';
	}
	if (j - 1 >= 0 && (map[i][j - 1] == '0' || map[i][j - 1] == '2'))
	{
		changed = 1;
		map[i][j - 1] = 'X';
	}
	return (changed);
}

char		*ft_set_tex(t_map *map_struct, int i, char *oldtex)
{
	int		j;
	int		len;
	int		len_2;
	char	*tex;

	j = 0;
	len_2 = 0;
	if (oldtex != NULL)
		ft_parse_error(MULTITEX);
	while (map_struct->file[i][j] != '.')
		j++;
	len = ft_test(map_struct, i, j);
	if (!(tex = wrmalloc((len + 1) * (sizeof(char)))))
		ft_parse_error(MALLOC);
	while (len_2 <= len)
	{
		tex[len_2] = map_struct->file[i][j + len_2];
		len_2++;
	}
	tex[len] = '\0';
	return (tex);
}
