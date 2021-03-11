/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:05:10 by mdavid            #+#    #+#             */
/*   Updated: 2019/04/25 15:57:27 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_isnegative(int n)
{
	if (n >= 0)
		return (0);
	else
		return (1);
}

static void		ft_abs(unsigned int *un, int *n)
{
	if (*n < 0)
		*un = (*n == -2147483648) ? 2147483648 : -(*n);
	else
		*un = *n;
}

char			*ft_itoa(int n)
{
	int				lenstr;
	char			*str;
	unsigned int	un;

	lenstr = 0;
	ft_abs(&un, &n);
	while ((un / ft_power(10, lenstr)) > 0)
	{
		lenstr++;
	}
	lenstr = lenstr + ft_isnegative(n);
	if (n == 0)
		lenstr = 1;
	if (!(str = (char*)malloc(sizeof(char) * (lenstr + 1))))
		return (NULL);
	str[lenstr] = '\0';
	if (n < 0)
		str[0] = '-';
	while (--lenstr >= ft_isnegative(n))
	{
		str[lenstr] = '0' + (un % 10);
		un = un / 10;
	}
	return (str);
}
