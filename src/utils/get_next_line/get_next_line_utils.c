/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:44:39 by seruiz            #+#    #+#             */
/*   Updated: 2021/01/26 15:24:06 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/get_next_line.h"

int			ft_free(char *s1, char *s2, t_fd_list *lst)
{
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	if (lst->buff != NULL)
		free(lst->buff);
	return (-1);
}

int			ft_eof(t_fd_list *lst)
{
	if (lst->buff != NULL)
		free(lst->buff);
	lst->buff = NULL;
	return (0);
}

size_t		ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
