/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:11:03 by mdavid            #+#    #+#             */
/*   Updated: 2019/04/18 16:15:08 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *nee, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (nee[0] == '\0')
		return ((char*)hay);
	while (hay[i] && i < len)
	{
		j = 0;
		while ((hay[i + j] == nee[j]) && (hay[i + j] && nee[j])
				&& (i + j <= len))
		{
			j++;
		}
		if (nee[j] == '\0')
			return ((char*)(hay + i));
		i++;
	}
	return (NULL);
}
