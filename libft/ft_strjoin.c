/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:02:01 by mdavid            #+#    #+#             */
/*   Updated: 2019/06/26 14:41:05 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		lens1;
	size_t		lens2;
	char		*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(str = (char*)malloc(sizeof(char) * (lens1 + lens2 + 1))))
		return (NULL);
	while (i + 1 <= lens1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i + 1 <= lens1 + lens2)
	{
		str[i] = s2[i - lens1];
		i++;
	}
	str[i] = '\0';
	return (str);
}
