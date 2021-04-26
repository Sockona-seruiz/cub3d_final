/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 10:59:07 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/28 13:57:37 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/print_image.h"
#include "./../../includes/cube3d.h"

/*
**  PRINT_IMAGE
**  open a binary file is the same thing than normal file
**	O_CREAT can create the image with the permissions after it
*/

static int		open_many_file(void)
{
	static int	nbr;
	char		str[12];
	int			fd;

	if (nbr > 99)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("A bastard tried to catch more than 100 pictures !\n", 2);
		return (-2);
	}
	ft_memcpy(str, "image--.bmp", 11);
	str[5] = nbr / 10 + '0';
	str[6] = nbr % 10 + '0';
	str[11] = 0;
	nbr++;
	fd = open(str, O_WRONLY | O_CREAT, 00755);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nOpen failed\n", 2);
		return (-1);
	}
	return (fd);
}

static void		fill_bmp_header(t_renderer *rdr, int fd)
{
	t_bitmap bitmap;

	ft_memcpy(bitmap.fileheader.signature, "BM", 2);
	bitmap.fileheader.filesize = rdr->r_size * 3 + sizeof(t_bitmap);
	bitmap.fileheader.reserved = 0;
	bitmap.fileheader.fileoffset_to_pixelarray = sizeof(t_bitmap);
	bitmap.imageheader.dibheadersize = sizeof(t_imageheader);
	bitmap.imageheader.width = rdr->r_wid;
	bitmap.imageheader.height = rdr->r_hei;
	bitmap.imageheader.planes = 1;
	bitmap.imageheader.bitsperpixel = 24;
	bitmap.imageheader.compression = 0;
	bitmap.imageheader.imagesize = rdr->r_size;
	bitmap.imageheader.ypixelpermeter = _YPIXELPERMETER;
	bitmap.imageheader.xpixelpermeter = _XPIXELPERMETER;
	bitmap.imageheader.numcolorspallette = 0;
	bitmap.imageheader.mostimpcolor = 0;
	write(fd, &bitmap.fileheader, 14);
	write(fd, &bitmap.imageheader, sizeof(t_imageheader));
}

static int		init_rev_image(t_renderer *rdr, t_bgr **rev_image)
{
	int		cpy;
	int		i;
	int		j;
	char	*image;

	image = (char *)rdr->img_data;
	if (!(*rev_image = malloc(rdr->r_size * sizeof(t_bgr))))
		return (-1);
	i = 0;
	while (i < rdr->r_hei)
	{
		j = rdr->r_wid - 1;
		while (j >= 0)
		{
			cpy = rdr->r_wid * i + j;
			(*rev_image)[cpy].blue = image[cpy * 4];
			(*rev_image)[cpy].green = image[cpy * 4 + 1];
			(*rev_image)[cpy].red = image[cpy * 4 + 2];
			j--;
		}
		i++;
	}
	return (0);
}

static void		fill_image(t_renderer *rdr, t_bgr *rev_image, int fd)
{
	int		i;
	int		remainder;
	char	c_null;
	char	c_huge;

	c_null = 0;
	c_huge = 0xFF;
	i = rdr->r_hei - 1;
	while (i >= 0)
	{
		remainder = 4 - (rdr->r_wid * sizeof(t_bgr)) % 4;
		if (remainder == 4)
			remainder = 0;
		write(fd, rev_image + i * rdr->r_wid, rdr->r_wid * sizeof(t_bgr));
		while (remainder > 1)
			remainder -= write(fd, &c_null, 1);
		write(fd, &c_huge, remainder);
		i--;
	}
}

int				print_image(t_renderer *rdr, t_ch *ch)
{
	int		fd;
	t_bgr	*rev_image;

	ch->save = 0;
	fd = open_many_file();
	if (fd < 0)
		ft_parse_error(SAVEERR);
	fill_bmp_header(rdr, fd);
	if (init_rev_image(rdr, &rev_image) == -1)
	{
		close(fd);
		ft_parse_error(SAVEERR);
	}
	fill_image(rdr, rev_image, fd);
	free(rev_image);
	close(fd);
	return (0);
}
