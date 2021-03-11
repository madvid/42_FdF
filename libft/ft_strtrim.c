/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:21:02 by mdavid            #+#    #+#             */
/*   Updated: 2019/04/25 19:38:49 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_strcpy_se(char *dst, char const *src, size_t st, size_t ed)
{
	size_t	i;

	i = 0;
	while (i + st <= ed)
	{
		dst[i] = (char)(src[st + i]);
		i++;
	}
	dst[i] = '\0';
}

char			*ft_strtrim(char const *s)
{
	size_t			i;
	size_t			start;
	size_t			end;
	char			*str;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && (i > 0))
		i--;
	end = i;
	i = 0;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && (s[i]))
		i++;
	start = i;
	if (s[0] == '\0' || start > end)
		return ((str = ft_memalloc(1)));
	if (!(str = (char*)malloc(sizeof(char) * (end - start + 1))))
		return (NULL);
	ft_strcpy_se(str, s, start, end);
	return ((char*)str);
}
