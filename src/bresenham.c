/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:17:34 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/11 19:37:33 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "../include/fdf.h"

/*
** FONCTION : BRESENHAM
** PARAMETRE(S) : ...
** DESCRIPTION :
**		Applique l'algorithme de Bresenham.
**RETOUR :
**		rien.
*/

void	add_pixel(int x, int y, t_img *img, int color)
{
	if (x > 0 && x < IMG_LX && y > 0 && y < IMG_LY)
		img->pixels[x + IMG_LX * y] = color;
}

/*
** FONCTION : BRESENHAM
** PARAMETRE(S) : ...
** DESCRIPTION :
**		Applique l'algorithme de Bresenham.
**RETOUR :
**		rien.
*/

void	bresenham(t_fpt p0, t_fpt p1, t_img *img, int color)
{
	int		err;

	err = (int)fabs((double)(p1.x - p0.x)) - (int)fabs((double)(p1.y - p0.y));
	while (1)
	{
		add_pixel((int)round(p0.x), (int)round(p0.y), img, color);
		if (2 * err >= -(int)fabs((double)(p1.y - p0.y)))
		{
			if ((int)round(p0.x) == (int)round(p1.x))
				break ;
			err += -(int)fabs((double)(p1.y - p0.y));
			p0.x += (p0.x < p1.x) ? 1 : -1;
		}
		if (2 * err <= (int)fabs((double)(p1.x - p0.x)))
		{
			if ((int)round(p0.y) == (int)round(p1.y))
				break ;
			err += (int)fabs((double)(p1.x - p0.x));
			p0.y += (p0.y < p1.y) ? 1 : -1;
		}
	}
}

/*
** FONCTION : STOCK_TO_PT
** PARAMETRES : ..
** DESCRIPTION :
**		...
** RETOUR :
**		...
*/

t_fpt	ft_pt(int ind, t_img *img)
{
	t_fpt	p;

	p.x = img->p_tab[0][ind];
	p.y = img->p_tab[1][ind];
	p.z = img->i_tab[2][ind];
	return (p);
}

/*
** FONCTION : BRESENHAM
** PARAMETRES :	int lx : .
**				int ly : .
**				t_img *img : .
** DESCRIPTION :
**		Applique l'algorithme de Bresenham.
** RETOUR :
**		rien.
*/

void	link_points(int lx, int ly, t_img *img)
{
	int		x;
	int		y;
	double	**tab;

	x = -1;
	y = -1;
	tab = img->p_tab;
	while (++y < ly)
	{
		x = -1;
		while (++x < lx)
		{
			if (x + 1 < lx)
				bresenham(ft_pt(x + lx * y, img), ft_pt(x + lx * y + 1, img),
				img, img->i_tab[3][x + lx * y]);
			if (y + 1 < img->nb_l)
				bresenham(ft_pt(x + lx * y, img), ft_pt(x + lx * (y + 1), img),
				img, img->i_tab[3][x + lx * y]);
		}
	}
}
