/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:55:54 by seruiz            #+#    #+#             */
/*   Updated: 2021/01/26 15:24:06 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	*get_img_2(t_tex *tex, t_renderer *rdr, char *path, char ori)
{
	int i;

	i = 0;
	while (path[i])
		i++;
	if (ori == 'E')
	{
		return (mlx_xpm_file_to_image(rdr->mlx_ptr, tex->path_e,
				&tex->east_w, &tex->east_h));
	}
	else if (ori == 'W')
	{
		return (mlx_xpm_file_to_image(rdr->mlx_ptr, tex->path_w,
				&tex->west_w, &tex->west_h));
	}
	return (NULL);
}

void	*get_img(t_tex *tex, t_renderer *rdr, char *path, char ori)
{
	int		i;

	i = 0;
	while (path[i])
		i++;
	if (ori == 'N')
	{
		return (mlx_xpm_file_to_image(rdr->mlx_ptr, tex->path_n,
					&tex->north_w, &tex->north_h));
	}
	else if (ori == 'S')
	{
		return (mlx_xpm_file_to_image(rdr->mlx_ptr, tex->path_s,
				&tex->south_w, &tex->south_h));
	}
	return (get_img_2(tex, rdr, path, ori));
}

t_tex	*init_tex_2(t_tex *tex, t_renderer *rdr)
{
	void	*buff;
	int		osef;

	buff = NULL;
	if ((buff = get_img(tex, rdr, tex->path_e, 'E')) == NULL)
		ft_parse_error(IMGERR);
	tex->tex_e = (unsigned int *)mlx_get_data_addr(buff,
				&rdr->img.bpp, &osef, &rdr->img.endian);
	tex->w_r_tex_e = tex->east_w / (float)MAP_RES;
	tex->h_r_tex_e = tex->east_h;
	buff = NULL;
	if ((buff = get_img(tex, rdr, tex->path_w, 'W')) == NULL)
		ft_parse_error(IMGERR);
	tex->tex_w = (unsigned int *)mlx_get_data_addr(buff,
				&rdr->img.bpp, &osef, &rdr->img.endian);
	tex->w_r_tex_w = tex->west_w / (float)MAP_RES;
	tex->h_r_tex_w = tex->west_h;
	tex->east_len = tex->east_h * tex->east_w;
	tex->west_len = tex->west_h * tex->west_w;
	return (tex);
}

t_tex	*init_tex(t_tex *tex, t_renderer *rdr)
{
	void	*buff;
	int		osef;

	buff = NULL;
	if ((buff = get_img(tex, rdr, tex->path_n, 'N')) == NULL)
		ft_parse_error(IMGERR);
	tex->tex_n = (unsigned int *)mlx_get_data_addr(buff,
				&rdr->img.bpp, &osef, &rdr->img.endian);
	tex->w_r_tex_n = tex->north_w / (float)MAP_RES;
	tex->h_r_tex_n = tex->north_h;
	buff = NULL;
	if ((buff = get_img(tex, rdr, tex->path_s, 'S')) == NULL)
		ft_parse_error(IMGERR);
	tex->tex_s = (unsigned int *)mlx_get_data_addr(buff,
				&rdr->img.bpp, &osef, &rdr->img.endian);
	tex->w_r_tex_s = tex->south_w / (float)MAP_RES;
	tex->h_r_tex_s = tex->south_h;
	tex->north_len = tex->north_h * tex->north_w;
	tex->south_len = tex->south_h * tex->south_w;
	return (init_tex_2(tex, rdr));
}
