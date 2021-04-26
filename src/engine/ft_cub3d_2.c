/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:56:32 by seruiz            #+#    #+#             */
/*   Updated: 2021/01/26 15:24:06 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"

void		ft_init_rdr_2(t_renderer *rdr, int width, int height)
{
	rdr->r_wid = width;
	rdr->r_hei = height;
	rdr->r_hei_2 = height / 2;
	rdr->r_size = width * height;
	rdr->img.bpp = 0;
	rdr->img.size_l = 0;
	rdr->img.endian = 0;
}

t_renderer	*init_rdr(int width, int height, int color_floor,
			unsigned int color_roof)
{
	t_renderer		*rdr;
	unsigned int	*colors;

	rdr = NULL;
	if (!(rdr = wrmalloc(sizeof(t_renderer))))
		ft_parse_error(MALLOC);
	if (!(colors = wrmalloc(2 * (sizeof(unsigned int)))))
		return (NULL);
	colors[0] = color_floor;
	colors[1] = color_roof;
	rdr->mlx_ptr = mlx_init();
	rdr->win = mlx_new_window(rdr->mlx_ptr, width, height, "GOTTA GO FAST");
	if (rdr->mlx_ptr == NULL)
		return (NULL);
	ft_init_rdr_2(rdr, width, height);
	rdr->img_ptr = mlx_new_image(rdr->mlx_ptr, width, height);
	rdr->img_data = (unsigned int *)mlx_get_data_addr(rdr->img_ptr,
					&rdr->img.bpp, &rdr->img.size_l, &rdr->img.endian);
	rdr->deg_power = (rdr->r_hei / 4);
	rdr->color_tab = colors;
	rdr->step = height / rdr->deg_power;
	rdr->wid_len = (width * height) - 1;
	return (rdr);
}
