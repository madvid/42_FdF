/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:53:23 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/29 14:08:46 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/fdf.h"

/*
** FONCTION : CENTER_TO_PT
** PARAMETRES :	t_img *img :la structure contenant l'image.
** 				t_fpt *pt : le point sur lequel centrer.
** DESCRIPTION :
**		Translate l'image pour qu'elle soit centrée sur 'pt'.
** RETOUR :
**		RIEN.
*/

int		ft_center_to_pt(t_mlx **mlx, t_img *img, t_fpt *pt)
{
	int		trans_x;
	int		trans_y;
	t_fpt	*tmp;

	if (!(tmp = (t_fpt*)malloc(sizeof(t_fpt))))
	{
		ft_free_mlx(mlx, 13);
		return (0);
	}
	calc_centers(img, tmp);
	trans_x = pt->x - tmp->x;
	trans_y = pt->y - tmp->y;
	free(tmp);
	ft_translation(trans_x, trans_y, img);
	return (1);
}

/*
** FONCTION : CALC_CENTERS
** PARAMETRES : t_img *img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		La fonction calcul le centre de la map transformée (subisant au fur
**		et à mesure les transformations) à partir des 4 coins de la map.
** RETOUR :
**		center	: le centre de la map.
*/

t_fpt	*calc_centers(t_img *img, t_fpt *center)
{
	int		l;
	int		c;
	double	**p_tab;

	l = img->nb_l;
	c = img->nb_c;
	p_tab = img->p_tab;
	center->x = (p_tab[0][0] + p_tab[0][c - 1] + p_tab[0][(c - 1)
	* (l - 2) + 1] + p_tab[0][(c - 1) * (l - 1)]) / 4;
	center->y = (p_tab[1][0] + p_tab[1][c - 1] + p_tab[1][(c - 1)
	* (l - 2) + 1] + p_tab[1][(c - 1) * (l - 1)]) / 4;
	center->z = (p_tab[2][0] + p_tab[2][c - 1] + p_tab[2][(c - 1)
	* (l - 2) + 1] + p_tab[2][(c - 1) * (l - 1)]) / 4;
	return (center);
}
