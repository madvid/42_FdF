/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:19:24 by mdavid            #+#    #+#             */
/*   Updated: 2019/04/26 12:10:58 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *hay, const char *nee)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (nee[0] == '\0')
		return ((char*)hay);
	while (hay[i])
	{
		j = 0;
		if (hay[i] == nee[j])
		{
			while ((hay[i + j] == nee[j]) && (hay[i + j] && nee[j]))
				j++;
		}
		if (nee[j] == '\0')
			return (((char*)hay) + i);
		i++;
	}
	return (NULL);
}
