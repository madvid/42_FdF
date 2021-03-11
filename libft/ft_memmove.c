/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:47:57 by mdavid            #+#    #+#             */
/*   Updated: 2019/04/17 20:18:20 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_overlapn_ptr(void *s1, const void *s2, size_t len)
{
	if ((s2 <= s1) && ((s2 + len) >= s1))
		return (1);
	else if ((s2 >= s1) && (s2 <= s1 + len))
		return (1);
	else
		return (0);
}

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;

	i = 0;
	if (ft_overlapn_ptr(dst, src, len) == 0)
		ft_memcpy(dst, src, len);
	else if (dst < src)
	{
		while (i < len)
		{
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			((unsigned char*)dst)[len - 1] = ((unsigned char*)src)[len - 1];
			len--;
		}
	}
	return (dst);
}
