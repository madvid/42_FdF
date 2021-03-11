/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:38:13 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/05 12:01:11 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strdupfree(char **dest, char **src)
{
	if (*dest)
	{
		ft_strclr(*dest);
		ft_strdel(dest);
	}
	if (*src)
	{
		*dest = ft_strdup(*src);
		ft_strclr(*src);
		ft_strdel(src);
	}
	return ((*dest == NULL && *src == NULL) ? -1 : 0);
}
