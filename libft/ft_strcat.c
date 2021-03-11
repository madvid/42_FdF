/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:00:26 by mdavid            #+#    #+#             */
/*   Updated: 2019/04/17 11:35:54 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	size_t		i;
	size_t		ldst;

	i = 0;
	ldst = ft_strlen(dst);
	while (src[i] != 0)
	{
		dst[ldst + i] = src[i];
		i++;
	}
	dst[i + ldst] = '\0';
	return (dst);
}
