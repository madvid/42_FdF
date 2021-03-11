/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:21:41 by mdavid            #+#    #+#             */
/*   Updated: 2019/04/29 11:07:03 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_nbline_is(char const *str, char *c, unsigned int *nbl)
{
	unsigned int	i;

	i = 0;
	*nbl = 0;
	while (str[i] && str[i] == *c)
		i = i + 1;
	while (str[i])
	{
		while (str[i] != *c && str[i])
			i++;
		(*nbl)++;
		while (str[i] && str[i] == *c)
			i = i + 1;
	}
}

static int		ft_nbchar_is(char const *s, char c, unsigned int *ind)
{
	int		nb;

	nb = 0;
	while (s[*ind] && s[*ind] == c)
		*ind = *ind + 1;
	while ((s[*ind]) && (s[*ind] != c))
	{
		nb++;
		*ind = *ind + 1;
	}
	return (nb);
}

static void		ft_filltab(char const *s, char c, char **tab, unsigned int *nbl)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	ln;

	i = 0;
	ln = 0;
	if (*nbl > 0)
	{
		while (ln < *nbl)
		{
			j = 0;
			while (s[i] && s[i] == c)
				i = i + 1;
			while ((s[i + j]) && (s[i + j] != c))
			{
				tab[ln][j] = s[i + j];
				j++;
			}
			tab[ln][j] = '\0';
			ln++;
			i = i + j;
		}
	}
	tab[*nbl] = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	char			**tab;
	unsigned int	nbl;
	unsigned int	nbc;
	unsigned int	i;
	unsigned int	j;

	if (s == NULL)
		return (NULL);
	ft_nbline_is(s, &c, &nbl);
	i = 0;
	j = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * (nbl + 1))))
		return (NULL);
	while (i < nbl)
	{
		nbc = ft_nbchar_is(s, c, &j);
		if (!(tab[i] = (char*)malloc(sizeof(char) * (nbc + 1))))
		{
			ft_eraser((void**)tab, i);
			return (NULL);
		}
		i++;
	}
	ft_filltab(s, c, tab, &nbl);
	return (tab);
}
