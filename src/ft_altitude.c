/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_altitude.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 13:05:31 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/04 17:26:28 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../include/fdf.h"

/*
** FONCTION : FIND_MIN
** PARAMETRES :	int *tab (ligne d'un tableau de int)
**				nb_pt (longeur de la ligne de int)
** DESCRIPTION :
**		Explore la ligne du tableau à la recherche du minimum
** RETOUR :
**		NULL / min	: NULL si la ligne est NULL
**					  le minimum de la ligne.
*/

int		ft_find_min(double *min, double *tab, int nb_pt)
{
	int		i;

	i = 0;
	if (tab == NULL)
		return (0);
	*min = tab[i];
	while (i < nb_pt)
	{
		if (tab[i] < *min)
			*min = tab[i];
		i++;
	}
	return (1);
}

/*
** FONCTION : FIND_MAX
** PARAMETRES :	int *tab (ligne d'un tableau de int)
**				nb_pt (longeur de la ligne de int)
** DESCRIPTION :
**		Explore la ligne du tableau à la recherche du maximum
** RETOUR :
**		NULL / max	: NULL si la ligne est NULL
**					  le maximum de la ligne.
*/

int		ft_find_max(double *max, double *tab, int nb_pt)
{
	int		i;

	i = 0;
	if (tab == NULL)
		return (0);
	*max = tab[i];
	while (i < nb_pt)
	{
		if (*max < tab[i])
			*max = tab[i];
		i++;
	}
	return (1);
}

/*
** FONCTION : DO_ALT
** PARAMETRES :	int sign : distingue entre -z (-1) et +z (1).
**				t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				t_img *img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Autorise l'événement d'augmentation ou de diminution de l'atitude et
**		permet ainsi de borner l'altitude minimale et maximale.
** RETOUR :
**		0 si le zoom est refusé, 1 sinon.
*/

int		ft_do_alt(int sign, t_events *events, t_img *img)
{
	double	min_z;
	double	max_z;

	if (sign == 1 && (int)(events->alt * 10) > 1000)
		return (0);
	if (sign == -1 && (int)(events->alt * 10) < 5)
		return (0);
	if ((int)(events->d_alt * 10) > 50 || (int)(events->d_alt * 10) < 2)
		return (0);
	if (events->alt + sign * events->d_alt <= 0
	|| events->alt + sign * events->d_alt >= 50)
		return (0);
	ft_find_min(&min_z, img->p_tab[2], img->nb_c * img->nb_l - 1);
	ft_find_max(&max_z, img->p_tab[2], img->nb_c * img->nb_l - 1);
	if (sign == -1
	&& (int)fabs(min_z * (events->alt + sign * events->d_alt)) <= -600000)
		return (0);
	if (sign == 1
	&& (int)fabs(max_z * (events->alt + sign * events->d_alt)) >= 600000)
		return (0);
	return (1);
}

/*
** FONCTION : ALTITUDE
** PARAMETRES :	keycode : valeur de la touche pressée.
**				*events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				*img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Applique une élévation/réduction d'altitude à la carte.
** RETOUR :
**		RIEN.
*/

int		ft_altitude(int keycode, t_mlx **mlx, t_events *events, t_img *img)
{
	int		sign;
	int		i;

	i = -1;
	sign = (keycode == 24) ? 1 : -1;
	if (ft_do_alt(sign, events, img) == 1)
	{
		events->alt = events->alt + sign * events->d_alt;
		while (++i < img->nb_c * img->nb_l)
		{
			img->p_tab[0][i] = img->i_tab[0][i] + (i % img->nb_c) * events->dst;
			img->p_tab[1][i] = img->i_tab[1][i] + (i / img->nb_c) * events->dst;
			img->p_tab[2][i] = (img->i_tab[2][i] + events->dst) * events->alt;
		}
		ft_rot_xyz(events, img);
		if (ft_center_to_pt(mlx, img, img->center) == 0)
		{
			ft_free_mlx(mlx, 12);
			return (0);
		}
	}
	return (1);
}
