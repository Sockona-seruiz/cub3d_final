/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 14:32:57 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/28 13:22:45 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_IMAGE_H
# define PRINT_IMAGE_H

# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include "./cube3d.h"

# define _XPIXELPERMETER 0xEC4
# define _YPIXELPERMETER 0xEC4
# define DPI 72

typedef struct __attribute__((packed))		s_fileheader
{
	unsigned char	signature[2];
	unsigned int	filesize;
	unsigned int	reserved;
	unsigned int	fileoffset_to_pixelarray;
}					t_fileheader;

typedef struct __attribute__((packed))		s_imageheader
{
	unsigned int	dibheadersize;
	unsigned int	width;
	unsigned int	height;
	int16_t			planes;
	int16_t			bitsperpixel;
	unsigned int	compression;
	unsigned int	imagesize;
	unsigned int	xpixelpermeter;
	unsigned int	ypixelpermeter;
	unsigned int	numcolorspallette;
	unsigned int	mostimpcolor;
}					t_imageheader;

typedef struct __attribute__((packed))		s_bitmap
{
	t_fileheader	fileheader;
	t_imageheader	imageheader;
}					t_bitmap;

typedef struct		s_bgr
{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
}					t_bgr;

#endif
