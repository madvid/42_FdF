/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_tab_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:16:16 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/04 17:27:05 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
** FONCTION : INT_TAB_DUP
** PARAMETRES :	int **i_tab : le tableau contenant les points de la map.
**				int nb_pt : le nb de points(colonnes) dans le tableau i _tab.
** DESCRIPTION :
**		Dupplique le tableau i_tab supposé en 2D (3 lignes etnb_pt colonnes).
** RETOUR :
**		NULL / **cpy_tab	-> NULL si pb d'allocation / **i_tab = NULL.
**							-> une copie de i_tab.
*/

int		**ft_int_tab_dup(int **i_tab, int nb_pt)
{
	int		**cpy_tab;
	int		i;

	cpy_tab = ft_table_int(3, nb_pt);
	i = -1;
	while (++i < nb_pt)
	{
		cpy_tab[0][i] = i_tab[0][i];
		cpy_tab[1][i] = i_tab[1][i];
		cpy_tab[2][i] = i_tab[2][i];
	}
	return (cpy_tab);
}
