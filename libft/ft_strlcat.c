/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:59:15 by mdavid            #+#    #+#             */
/*   Updated: 2019/04/19 14:32:57 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ldst;
	size_t	lsrc;
	size_t	i;

	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (lsrc);
	while (src[i] && i + ldst + 1 < size)
	{
		dst[ldst + i] = src[i];
		i++;
	}
	dst[i + ldst] = '\0';
	if (size < ldst)
		return (size + lsrc);
	return (ldst + lsrc);
}
