/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:19:54 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/03 14:51:23 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"
#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_assign_tex(t_tex *tex, t_map *map_struct)
{
	tex->path_n = map_struct->tex_n;
	tex->path_s = map_struct->tex_s;
	tex->path_e = map_struct->tex_e;
	tex->path_w = map_struct->tex_w;
	map_struct->sprite->path = map_struct->sprt;
	if (map_struct->sprt == NULL)
		map_struct->issprta = 1;
	map_struct->sprite->anim_path = map_struct->sprta;
}

int		main(int argc, char **argv)
{
	char			*line;
	t_map			*map_struct;
	t_tex			*tex;
	int				fd;

	line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_parse_error(MAPERR);
	if ((map_struct = wrmalloc(sizeof(t_map))) == 0)
		return (-1);
	map_struct = ft_gnl_map(fd, argv[1], map_struct);
	if ((tex = wrmalloc(sizeof(t_tex))) == 0)
		return (-1);
	if ((map_struct->sprite = wrmalloc(sizeof(t_sprite_info))) == 0)
		return (-1);
	ft_bzero_struct(map_struct);
	if (argc == 3 && (ft_strncmp(argv[2], "--save", 6)) == 0)
		map_struct->save = 1;
	ft_parse_inf(map_struct);
	ft_assign_tex(tex, map_struct);
	open_window(map_struct->map, map_struct->mapy, tex, map_struct);
	return (0);
}
