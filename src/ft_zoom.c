/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:21:06 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/04 17:26:57 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "../include/fdf.h"

/*
** FONCTION : DO_ZOOM
** PARAMETRES :	int sign : distingue entre dézoome (-1) et zoom (1).
**				t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				t_img *img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Autorise l'événement de dézoom ou zoom et permet ainsi de borner la
**		disctance entre 2 points adjacents.
** RETOUR :
**		0 si le zoom est refusé, 1 sinon.
*/

int		ft_do_zoom(int sign, t_events *events, t_img *img)
{
	int		do_zoom;
	int		dist_x;
	int		dist_y;

	do_zoom = 0;
	dist_x = abs((int)round(img->p_tab[0][1] - img->p_tab[0][0]));
	dist_y = abs((int)round(img->p_tab[1][img->nb_c] - img->p_tab[1][0]));
	if (sign == -1 && (dist_x > events->d_dst + 2
	&& dist_y > events->d_dst + 2))
		do_zoom = 1;
	if (sign == 1 && (dist_x + events->d_dst < 100
	&& dist_y + events->d_dst < 100))
		do_zoom = 1;
	return (do_zoom);
}

/*
** FONCTION : ZOOM
** PARAMETRES :	keycode : valeur de la touche pressée.
**				*events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				*img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Applique le zoom/dezoom s'il est autorisé.
** RETOUR :
**		rien.
*/

int		ft_zoom(int keycode, t_mlx **mlx, t_events *events, t_img *img)
{
	int		i;
	int		sign;

	i = -1;
	sign = (keycode == 69) ? 1 : -1;
	if (ft_do_zoom(sign, events, img) == 1)
	{
		events->dst = events->dst + sign * events->d_dst;
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
