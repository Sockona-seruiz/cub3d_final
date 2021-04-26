/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:21:58 by seruiz            #+#    #+#             */
/*   Updated: 2021/02/03 12:14:37 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
** writes a string to a fd
*/

#include <unistd.h>
#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
