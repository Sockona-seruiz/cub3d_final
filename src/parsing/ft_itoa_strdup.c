/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_strdup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:42:44 by seruiz            #+#    #+#             */
/*   Updated: 2021/01/26 15:24:06 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/get_next_line.h"

static int	ft_treatint(int n)
{
	int i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
	{
		i++;
		n = n * (-1);
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	ft_atoi_is_neg(int n, char *result)
{
	if (n == 0)
	{
		result[0] = '0';
		return (1);
	}
	else if (n < 0)
	{
		result[0] = '-';
		return (1);
	}
	return (0);
}

char		*ft_itoa(int n)
{
	char	*result;
	int		sign;
	int		i;
	int		j;

	result = NULL;
	sign = 0;
	i = ft_treatint(n);
	if ((result = (char *)wrmalloc(sizeof(char) * (i + 1))) == 0)
		return (0);
	j = ft_atoi_is_neg(n, result);
	if (j == 1 && n != 0)
		n = n * -1;
	while (n > 0)
	{
		result[i - 1] = (n % 10) + 48;
		n = n / 10;
		i--;
		j++;
	}
	result[j] = '\0';
	return (result);
}

char		*ft_strdup(char *s1)
{
	size_t	i;
	char	*dest;

	i = ft_strlen(s1);
	if (NULL == (dest = (char *)wrmalloc(sizeof(char) * (i + 1))))
		return (0);
	dest[i] = '\0';
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	return (dest);
}
