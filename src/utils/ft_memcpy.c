/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:52:53 by seruiz            #+#    #+#             */
/*   Updated: 2021/01/28 13:27:41 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
** copies n bytes from memory area src to memory area dst
*/

#include <stdlib.h>
#include "../../includes/cube3d.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	const char		*src2;
	char			*dest2;

	i = 0;
	if (!src && !dest)
		return (0);
	src2 = src;
	dest2 = dest;
	while (i < n)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest2);
}
