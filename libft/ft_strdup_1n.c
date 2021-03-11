/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_1n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:44:07 by mdavid            #+#    #+#             */
/*   Updated: 2019/06/27 13:44:29 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup_1n(const char *str)
{
	size_t			i;
	size_t			len;
	char			*strcp;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	if (!(strcp = (char*)malloc(sizeof(char) * (len + 2))))
		return (0);
	while (i < len)
	{
		strcp[i] = str[i];
		i++;
	}
	strcp[i] = '\n';
	strcp[i + 1] = '\0';
	return (strcp);
}
