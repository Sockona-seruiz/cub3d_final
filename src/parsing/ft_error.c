/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:47:51 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/03 14:51:36 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"

void	ft_parse_error_2(int erno)
{
	if (erno == FLOORMISS)
		printf("Error\nFloor color has an incomplete definition");
	else if (erno == OORCOLOR)
		printf("Error\nRoof or ceil color out of range [0 ; 255]");
	else if (erno == WRGCHARAC)
		printf("Error\nWrong character in map definition");
	else if (erno == MULTICH)
		printf("Error\nMultiple character posotion in map");
	else if (erno == NOTCLOSED)
		printf("Error\nThe map is not closed");
	else if (erno == MISSINFO)
		printf("Error\nInformation missing in '.cub' file");
	else if (erno == MALLOC)
		printf("Error\nA malloc failed");
	else if (erno == NOCH)
		printf("Error\nCharacter pos not initialized");
	else if (erno == IMGERR)
		printf("Error\nTexture path invalid");
	wrdestroy();
	exit(1);
}

void	ft_parse_error(int erno)
{
	if (erno == MAPERR)
		printf("Error\nMap path invalid");
	else if (erno == MULTITEX)
		printf("Error\nTexture path duplicate");
	else if (erno == FLOORERR)
		printf("Error\nFloor color duplicate");
	else if (erno == RESERR)
		printf("Error\nResolution instruction duplicate");
	else if (erno == ROOFERR)
		printf("Error\nRoof color duplicate");
	else if (erno == ROOFMISS)
		printf("Error\nRoof color has an incomplete definition");
	else if (erno == SAVEERR)
		printf("Error\nFailed to save bmp file");
	else if (erno == NOERROR)
	{
		wrdestroy();
		exit(0);
	}
	ft_parse_error_2(erno);
}
