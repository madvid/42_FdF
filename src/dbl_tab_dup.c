/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_tab_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 13:46:49 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/04 17:26:11 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
** FONCTION : DBL_TAB_DUP
** PARAMETRES :	double **i_tab (le tableau contenant les points de la map).
**				int nb_pt (le nb de points dans le tableau i _tab).
** DESCRIPTION :
**		Dupplique le tableau i_tab et est converti en double.
** RETOUR :
**		NULL / **cpy_tab	-> NULL si pb d'allocation / **i_tab = NULL.
**							-> une copie de i_tab avc castage en double.
*/

double	**ft_dbl_tab_dup(int **i_tab, int nb_pt)
{
	double		**cpy_tab;
	int			i;

	cpy_tab = ft_table_dbl(3, nb_pt);
	i = -1;
	while (++i < nb_pt)
	{
		cpy_tab[0][i] = (double)i_tab[0][i];
		cpy_tab[1][i] = (double)i_tab[1][i];
		cpy_tab[2][i] = (double)i_tab[2][i];
	}
	return (cpy_tab);
}
