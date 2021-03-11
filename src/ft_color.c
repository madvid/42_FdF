/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:57:21 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/14 13:38:50 by mdavid           ###   ########.fr       */
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

int		find_min(int *tab, int nb_pt)
{
	int		i;
	int		min;

	i = 0;
	min = tab[i];
	while (i < nb_pt)
	{
		if (tab[i] < min)
			min = tab[i];
		i++;
	}
	return (min);
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

int		find_max(int *tab, int nb_pt)
{
	int		i;
	int		max;

	i = 0;
	max = tab[i];
	while (i < nb_pt)
	{
		if (max < tab[i])
			max = tab[i];
		i++;
	}
	return (max);
}

int		ft_color(int z, int zi, int zf)
{
	int		red;
	int		green;
	int		blue;
	int		dz;
	double	sigma;

	dz = zf - zi;
	sigma = (3.0 / 5.0) * dz * (1 / sqrt(2 * log(2)));
	green = (int)(255 * exp(-pow((z - zi - 0.5 * dz) / (0.6 * sigma), 2)))
	<< 8;
	blue = (int)(255 * exp(-pow((z - zi) / (1.2 * sigma), 2))) << 0;
	red = (int)(255 * exp(-pow((z - zf) / (1.7 * sigma), 2))) << 16;
	return (red + green + blue);
}

/*
** FONCTION : ATTRIBUT_COLOR
** PARAMETRES : t_img *img : struc contenant les parametres relatives à la map.
** DESCRIPTION :
**		Permet d'attribuer
** RETOUR :
*/

void	ft_attribut_color(t_img *img)
{
	int		z_min;
	int		z_max;
	int		i;

	i = 0;
	z_min = find_min(img->i_tab[2], img->nb_c * img->nb_l);
	z_max = find_max(img->i_tab[2], img->nb_c * img->nb_l);
	while (i < img->nb_c * img->nb_l)
	{
		img->i_tab[3][i] = ft_color(img->i_tab[2][i], z_min, z_max);
		i++;
	}
}
