/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:40:50 by mdavid            #+#    #+#             */
/*   Updated: 2019/04/22 11:42:06 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_power(unsigned int n, int pow)
{
	int		i;
	size_t	result;

	i = -1;
	result = 1;
	while (++i < pow)
		result = result * n;
	return (result);
}
