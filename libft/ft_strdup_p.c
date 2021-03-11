/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:50:08 by mdavid            #+#    #+#             */
/*   Updated: 2019/06/26 16:33:34 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup_p(const char *str)
{
	size_t			i;
	size_t			len;
	char			*strcp;

	i = 0;
	len = ft_strlen(str);
	if (str == NULL)
		return (NULL);
	if (!(strcp = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i <= len)
	{
		strcp[i] = str[i];
		i++;
	}
	return (strcp);
}
