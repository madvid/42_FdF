/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:55:17 by mdavid            #+#    #+#             */
/*   Updated: 2019/04/18 18:46:48 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		i;

	i = 0;
	if (s[i] != '\0')
	{
		while (s[i] != (char)c && s[i] != '\0')
			i++;
		if (s[i] == '\0' && c != 0)
			return (NULL);
		return ((char*)(s + i));
	}
	else if (s[i] == '\0' && c == '\0')
		return ((char*)(s + i));
	else
		return (NULL);
}
