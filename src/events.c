/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:35:20 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/29 14:08:45 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "../include/fdf.h"

/*
** FONCTION :	INI_MIDDLE_TRANSL_DST
** PARAMETRES :	t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
** DESCRIPTION :
**		Initialise les parametres de translation dans events pour le
**		premier tracé.
**		Calcul également le milieu de la fenêtre.
** RETOUR :
**		RIEN.
*/

void	ini_middle_transl_dst(t_events *events)
{
	events->middle->x = IMG_LX / 2;
	events->middle->y = IMG_LY / 2;
	events->trans_l->x = 0;
	events->trans_l->y = 0;
	events->trans_l->z = 0;
	events->trans_dl->x = 4;
	events->trans_dl->y = 4;
	events->trans_dl->z = 4;
	events->dst = 10;
	events->d_dst = 2;
	events->alt = 1.0;
	events->d_alt = 0.2;
}

/*
** FONCTION :	INI_TRANSF_MATRIX
** PARAMETRES :	t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
** DESCRIPTION :
**		Initialise les parametres de pour la projection isometrique.
** RETOUR :
**		0/-1	si tout est ok/ il y a eu un pb d'allocation.
*/

void	ft_ini_transf_matrix(double **m_iso, double **m_cabinet)
{
	m_iso[0][0] = cos(45 * DEGTORAD);
	m_iso[0][1] = 0;
	m_iso[0][2] = -sin(45 * DEGTORAD);
	m_iso[1][0] = sin(35.264 * DEGTORAD) * sin(45 * DEGTORAD);
	m_iso[1][1] = cos(35.264 * DEGTORAD);
	m_iso[1][2] = sin(35.264 * DEGTORAD) * cos(45 * DEGTORAD);
	m_iso[2][0] = 0.0;
	m_iso[2][1] = 0.0;
	m_iso[2][2] = 0.0;
	m_cabinet[0][0] = 1;
	m_cabinet[0][1] = 0;
	m_cabinet[0][2] = 0.5 * cos(63.4 * DEGTORAD);
	m_cabinet[1][0] = 0;
	m_cabinet[1][1] = 1;
	m_cabinet[1][2] = 0.5 * sin(63.4 * DEGTORAD);
	m_cabinet[2][0] = 0.0;
	m_cabinet[2][1] = 0.0;
	m_cabinet[2][2] = 0.0;
}

/*
** FONCTION :	INI_ISO_PROJECT
** PARAMETRES :	t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
** DESCRIPTION :
**		Initialise les matrices de transformation des différents types de
**		projections.
** RETOUR :
**		0/-1	si tout est ok/ il y a eu un pb d'allocation.
*/

int		ini_project(t_mlx **mlx, t_events *events)
{
	int			i;

	i = -1;
	if (!(events->m_iso = ft_table_dbl(3, 3)))
	{
		ft_free_mlx(mlx, 10);
		return (0);
	}
	if (!(events->m_cabinet = ft_table_dbl(3, 3)))
	{
		ft_free_mlx(mlx, 11);
		return (0);
	}
	ft_ini_transf_matrix(events->m_iso, events->m_cabinet);
	return (1);
}

/*
** FONCTION :	INI_THETA
** PARAMETRES :	t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
** DESCRIPTION :
**		Initialise les parametres de translation dans events pour le
**		premier tracé.
** RETOUR :
**		RIEN.
*/

int		ini_theta(t_mlx **mlx, t_events *events)
{
	events->theta->x = 0;
	events->theta->y = 0;
	events->theta->z = 0;
	events->dtheta->x = 2;
	events->dtheta->y = 2;
	events->dtheta->z = 2;
	if (ini_project(mlx, events) == 0)
		return (0);
	return (1);
}

/*
** FONCTION :	INI_EVENTS
** PARAMETRES :	t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				t_img *img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Initialise les parametres de la struct t_events pour le premier tracé.
** RETOUR :
**		RIEN.
*/

int		ini_events(t_mlx **mlx, t_events *events, t_img *img)
{
	int		i;

	i = -1;
	ft_attribut_color(img);
	ini_middle_transl_dst(events);
	if (ini_theta(mlx, events) == 0)
		return (0);
	i = -1;
	while (++i < img->nb_c * img->nb_l)
	{
		img->p_tab[0][i] = img->i_tab[0][i] + (i % img->nb_c) * events->dst;
		img->p_tab[1][i] = img->i_tab[1][i] + (i / img->nb_c) * events->dst;
		img->p_tab[2][i] = (img->i_tab[2][i] + events->dst) * events->alt;
	}
	if (!(img->center = (t_fpt*)malloc(sizeof(t_fpt))))
	{
		ft_free_mlx(mlx, 12);
		return (0);
	}
	if (ft_center_to_pt(mlx, img, events->middle) == 0)
		return (0);
	img->center = calc_centers(img, img->center);
	return (1);
}
