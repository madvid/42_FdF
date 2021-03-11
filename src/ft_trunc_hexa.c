/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trunc_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 18:09:58 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/30 17:43:02 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/fdf.h"

/*
** FONCTION : IS_HEXADECIMAL
** PARAMETRES : char *line : chaine de caractères.
** DESCRIPTION :
**		Vérifie que la portion de (line + i) à (line + 7) est sous la forme de
**		'0x' +'RGB en hexa'.
** RETOUR :
**		-1/1 : si la portion de line [n'est pas / est] '0x+RGB(hexa)'
*/

int		ft_ishexadecimal(char *line)
{
	int		i;

	i = 0;
	if (line[i] == '0' && line[i + 1] == 'x')
		i = i + 2;
	while (i < 8)
	{
		if (!(line[i] >= '0' && line[i] <= '9') && !(line[i] >= 'a'
		&& line[i] <= 'f') && !(line[i] >= 'A' && line[i] <= 'F'))
			return (-1);
		i++;
	}
	return (1);
}

/*
** FONCTION : COMPT_HEXA
** PARAMETRES : char *str : chaine de caractères.
** DESCRIPTION :
**		Compte les portions de hexadecimales ('0x' +'RGB en hexa') et stocke
**		ce compte dans la variable compt.
** RETOUR :
**		RIEN.
*/

int		ft_compt_hexa(char *str)
{
	int		i;
	int		compt;

	i = 0;
	compt = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '-' || str[i] == '+' || str[i] == '\n')
			i++;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		if (str[i] == ',' && str[i])
		{
			i++;
			if (ft_ishexadecimal((str + i)) == 1)
				i = i + 8;
			compt = compt + 1;
		}
		if (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '-'
		&& str[i] != '+' && str[i] != '\n' && (ft_isdigit(str[i]) == 0))
			return (-1);
	}
	return ((str == NULL) ? -1 : compt);
}

/*
** FONCTION : TRUNC_HEXA
** PARAMETRES : char *str : chaine de caractères.
** DESCRIPTION :
**		Tronque les portions de hexadecimales ('0x' +'RGB en hexa').
** RETOUR :
**		-1/1 : si la portion de line [n'est pas / est] '0x+RGB(hexa)'
*/

char	*ft_trunc_hexa(char **l)
{
	int		compt;
	char	*ret;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if ((compt = ft_compt_hexa(*l)) == -1
	|| !(ret = (char*)ft_memalloc(ft_strlen(*l) - 9 * compt + 1)))
		return (NULL);
	if (ret != NULL)
	{
		while ((*l)[++i])
		{
			if ((*l)[i] == ',')
				i++;
			if (ft_ishexadecimal((*l + i)) == 1)
				i = i + 8;
			ret[++j] = (*l)[i];
		}
		ft_strdupfree(l, &ret);
	}
	return (*l);
}
