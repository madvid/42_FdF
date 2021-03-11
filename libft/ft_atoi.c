/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:00:19 by mdavid            #+#    #+#             */
/*   Updated: 2019/04/25 16:04:28 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *s)
{
	size_t		i;
	int			sign;
	size_t		result;

	i = 0;
	sign = 1;
	result = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		sign = (s[i] == '-') ? -1 : 1;
		i++;
	}
	while ((s[i] >= '0') && (s[i] <= '9'))
	{
		result = 10 * result + ((long long)s[i] - 48);
		i++;
		if (sign == 1 && result > LONG_MAX)
			return (-1);
		if (sign == -1 && result > (size_t)LONG_MAX + 1)
			return (0);
	}
	return ((int)(sign * result));
}
