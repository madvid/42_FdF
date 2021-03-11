/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_1n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:37:48 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/12 13:40:14 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_1n(char **s1, char const *s2)
{
	size_t		i;
	char		*str;

	if (s1 == NULL || *s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2)
	+ 2))))
		return (NULL);
	while (i + 1 <= ft_strlen(*s1))
	{
		str[i] = (*s1)[i];
		i++;
	}
	while (i + 1 <= ft_strlen(*s1) + ft_strlen(s2))
	{
		str[i] = s2[i - ft_strlen(*s1)];
		i++;
	}
	str[i] = '\n';
	str[i + 1] = '\0';
	ft_strdel(s1);
	return (str);
}
