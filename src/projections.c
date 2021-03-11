/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:53:50 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/04 17:27:14 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../include/fdf.h"

/*
** FONCTION : APPLY_PROJ
** PARAMETRES :	t_img img :
**				f
** DESCRIPTION :
**		Applique la matrice (matrix) de transformation sur l'ensemble des points
**		de la carte.
** RETOUR :
*/

void	ft_apply_proj(t_img *img, double **mtx)
{
	int		i;
	t_fpt	tmp;

	i = -1;
	while (++i < img->nb_c * img->nb_l)
	{
		tmp.x = img->p_tab[0][i];
		tmp.y = -img->p_tab[2][i];
		tmp.z = img->p_tab[1][i];
		img->p_tab[0][i] = tmp.x * mtx[0][0] + tmp.y * mtx[0][1]
		+ tmp.z * mtx[0][2];
		img->p_tab[1][i] = tmp.x * mtx[1][0] + tmp.y * mtx[1][1]
		+ tmp.z * mtx[1][2];
		img->p_tab[2][i] = tmp.x * mtx[2][0] + tmp.y * mtx[2][1]
		+ tmp.z * mtx[2][2];
	}
}

/*
** FONCTION : PROJECTIONS
** PARAMETRES : t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				t_img *img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Permet de passer à la vue isometrique.
** RETOUR :
**		RIEN.
*/

int		ft_projections(int keycode, t_mlx **mlx, t_events *events, t_img *img)
{
	int			j;

	j = -1;
	while (++j < img->nb_c * img->nb_l)
	{
		img->p_tab[0][j] = img->i_tab[0][j] + (j % img->nb_c) * events->dst;
		img->p_tab[1][j] = img->i_tab[1][j] + (j / img->nb_c) * events->dst;
		img->p_tab[2][j] = (img->i_tab[2][j] + events->dst) * events->alt;
	}
	if (keycode == 34)
	{
		events->stat_proj = 34;
		ft_apply_proj(img, events->m_iso);
	}
	if (keycode == 35)
	{
		events->stat_proj = 35;
		ft_apply_proj(img, events->m_cabinet);
	}
	if (ft_center_to_pt(mlx, img, img->center) == 0)
		ft_free_mlx(mlx, 12);
	return ((mlx == NULL) ? 0 : 1);
}
