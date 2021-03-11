/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:20:53 by mdavid            #+#    #+#             */
/*   Updated: 2019/06/26 15:03:53 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *cnt, size_t cnt_s)
{
	t_list		*nwlist;

	if (!(nwlist = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (cnt == NULL)
	{
		nwlist->cnt = NULL;
		nwlist->cnt_s = 0;
	}
	else
	{
		if (!(nwlist->cnt = (void*)malloc(sizeof(cnt))))
		{
			free(nwlist);
			return (NULL);
		}
		ft_memcpy(nwlist->cnt, cnt, cnt_s);
		nwlist->cnt_s = cnt_s;
	}
	nwlist->next = NULL;
	return (nwlist);
}
