/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 12:33:17 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/26 17:29:12 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"

/*
** FONCTION : FT_FREE_TABINT
** PARAMETRES :	int **table : tableau de int.
**				int nb_l : nb de ligne.
** DESCRIPTION :
**		Free le tableau passé en argument et ayant nb_l lignes.
**	RETOUR :
**		rien.
*/

void	ft_free_tabint(int **table, int nb_l)
{
	if (table)
	{
		while (nb_l > 0)
		{
			free(table[nb_l - 1]);
			nb_l--;
		}
		free((void*)table);
		table = NULL;
	}
}

/*
** FONCTION : FT_TABLE_INT_INIT.
** PARAMETRES :	int **table : tableau de int.
**				int nb_l : nb line de table.
**				int nb_c : nb column de table.
** DESCRIPTION :
**		Initialise l'ensemble des éléments de table à 0.
** RETOUR :
**		RIEN.
*/

void	ft_table_int_init(int **table, int nb_l, int nb_c)
{
	int		k;
	int		l;

	k = 0;
	while (k < nb_l)
	{
		l = 0;
		while (l < nb_c)
		{
			table[k][l] = 0;
			l++;
		}
		k++;
	}
}

/*
** FONCTION : FT_TABLE_INT
** PARAMETRE(S) :	int nb_l : nb de lignes.
**					int nb_c : nb de colonnes.
** DESCRIPTION :
**		Allocation d'un tableau de int de la taille (nb_c x nb_l).
** RETOUR :
**		NULL s'il y a eu une erreur lors de l'allocation.
**		un tableau de INT initialisé à 0 sinon.
*/

int		**ft_table_int(int nb_l, int nb_c)
{
	int		**table;
	int		i;

	i = 0;
	if (!(table = (int**)malloc(sizeof(int*) * nb_l)))
		return (NULL);
	while (i < nb_l)
	{
		if (!(table[i] = (int*)malloc(sizeof(int) * nb_c)))
		{
			while (--i >= 0)
				free(table[i]);
			free(table);
			return (NULL);
		}
		i++;
	}
	ft_table_int_init(table, nb_l, nb_c);
	return (table);
}
