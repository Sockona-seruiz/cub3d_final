/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:41:29 by seruiz            #+#    #+#             */
/*   Updated: 2021/01/26 15:24:06 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"

t_map		*ft_gnl_map_2(int fd, int count_line, char *path, t_map *map_struct)
{
	char	*line;
	int		ret;
	int		i;

	i = 0;
	if ((map_struct->file = wrmalloc(sizeof(char *) *
		(count_line + 2))) == NULL)
		ft_parse_error(MALLOC);
	map_struct->file[count_line + 1] = NULL;
	close(fd);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		map_struct->file[i] = ft_strdup(line);
		wrfree(line);
		i++;
		if (ret == 0)
			break ;
	}
	return (map_struct);
}

int			ft_gnl_map_wh(int i, int ret, char *buff, int count_line)
{
	while (i < 64 || i < ret)
	{
		if (buff[i] == '\n')
			count_line++;
		buff[i] = '\0';
		i++;
	}
	i = 0;
	return (count_line);
}

t_map		*ft_gnl_map(int fd, char *path, t_map *map_struct)
{
	int		count_line;
	char	*buff;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	count_line = 0;
	if ((buff = malloc(sizeof(char) * (64 + 1))) == NULL)
		ft_parse_error(MALLOC);
	buff[64] = '\0';
	while ((ret = read(fd, buff, 64)) > 0)
	{
		if (ret == -1)
		{
			wrfree(buff);
			ft_parse_error(MALLOC);
		}
		count_line = ft_gnl_map_wh(i, ret, buff, count_line);
	}
	map_struct->count_line = count_line;
	wrfree(buff);
	return (ft_gnl_map_2(fd, count_line, path, map_struct));
}
