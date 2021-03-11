/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 18:14:29 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/04 17:26:43 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "../include/fdf.h"

/*
** FONCTION :ROT_XYZ
** PARAMETRES :	*events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				*img : ptr sur struct contenant toutes les variables relatives
**				à l'image "principale".
** DESCRIPTION :
**		Applique les rotations d'angles Theta_x/y/z.
**		Les fct roation_x/y/z faisant la rotation avec dtheta_x/y/z, les val
**		de theta_x/y/z sont assignées a dtheta_x/y/z temporairement.
** RETOUR :
**		RIEN.
*/

void	ft_rot_xyz(t_events *events, t_img *i)
{
	int		j;
	t_fpt	a;
	t_fpt	p;

	j = -1;
	a.x = events->theta->x * DEGTORAD;
	a.y = events->theta->y * DEGTORAD;
	a.z = events->theta->z * DEGTORAD;
	while (++j < i->nb_c * i->nb_l)
	{
		p.x = i->p_tab[0][j] * cos(a.z) * cos(a.y) + i->p_tab[1][j]
		* (-sin(a.z) * cos(a.x) + cos(a.z) * sin(a.y) * sin(a.x))
		+ i->p_tab[2][j] * (sin(a.z) * sin(a.x) + cos(a.z) * cos(a.x)
		* sin(a.y));
		p.y = i->p_tab[0][j] * sin(a.z) * cos(a.y) + i->p_tab[1][j]
		* (cos(a.x) * cos(a.z) + sin(a.x) * sin(a.y) * sin(a.z))
		+ i->p_tab[2][j] * (-sin(a.x) * cos(a.z) + sin(a.z) * sin(a.y)
		* cos(a.x));
		p.z = -i->p_tab[0][j] * sin(a.y) + i->p_tab[1][j] * sin(a.x)
		* cos(a.y) + i->p_tab[2][j] * cos(a.y) * cos(a.x);
		i->p_tab[0][j] = p.x;
		i->p_tab[1][j] = p.y;
		i->p_tab[2][j] = p.z;
	}
}

/*
** FONCTION :	ROTATION_X
** PARAMETRES :	int sign : signe de l'angle de rotation
**				t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				*img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Permet d'appliquer la rotation theta_x.
** RETOUR :
**		rien.
*/

void	ft_rotation_x(int sign, t_events *events, t_img *img)
{
	int		i;
	double	t_x;
	double	y_p;
	double	z_p;

	i = -1;
	t_x = sign * events->dtheta->x * DEGTORAD;
	while (++i < img->nb_c * img->nb_l)
	{
		y_p = img->p_tab[1][i] * cos(t_x) + img->p_tab[2][i] * sin(t_x);
		z_p = -img->p_tab[1][i] * sin(t_x) + img->p_tab[2][i] * cos(t_x);
		img->p_tab[1][i] = y_p;
		img->p_tab[2][i] = z_p;
	}
}

/*
** FONCTION :	ROTATION_Y
** PARAMETRES :	int sign : signe de l'angle de rotation
**				t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				*img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Permet d'appliquer la rotation theta_y.
** RETOUR :
**		rien.
*/

void	ft_rotation_y(int sign, t_events *events, t_img *img)
{
	int		i;
	double	t_y;
	double	x_p;
	double	z_p;

	i = -1;
	t_y = sign * events->dtheta->y * DEGTORAD;
	while (++i < img->nb_c * img->nb_l)
	{
		x_p = img->p_tab[0][i] * cos(t_y) + img->p_tab[2][i] * sin(t_y);
		z_p = -img->p_tab[0][i] * sin(t_y) + img->p_tab[2][i] * cos(t_y);
		img->p_tab[0][i] = x_p;
		img->p_tab[2][i] = z_p;
	}
}

/*
** FONCTION :	ROTATION_Z
** PARAMETRES :	int sign : signe de l'angle de rotation
**				t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				*img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Permet d'appliquer la rotation theta_z.
** RETOUR :
**		rien.
*/

void	ft_rotation_z(int sign, t_events *events, t_img *img)
{
	int		i;
	double	t_z;
	double	x_p;
	double	y_p;

	i = -1;
	t_z = sign * events->dtheta->z * DEGTORAD;
	while (++i < img->nb_c * img->nb_l)
	{
		x_p = img->p_tab[0][i] * cos(t_z) - img->p_tab[1][i] * sin(t_z);
		y_p = img->p_tab[0][i] * sin(t_z) + img->p_tab[1][i] * cos(t_z);
		img->p_tab[0][i] = x_p;
		img->p_tab[1][i] = y_p;
	}
}

/*
** FONCTION :	ROTATION_XYZ
** PARAMETRES :	int keycode : valeur de la touche du clavier pressée.
**				t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				*img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Permet d'appliquer les différentes rotation theta_x/y/z.
**		Touche '1|2' du pad -> rotation -thetax|+thetax.
**		Touche '3|4' du pad -> rotation -thetay|+thetay.
**		Touche '5|6' du pad -> rotation -thetaz|+thetaz.
** RETOUR :
**		RIEN.
*/

int		ft_rotation_xyz(int keycode, t_mlx **mlx, t_events *events, t_img *img)
{
	int		i;
	int		sign;

	i = -1;
	sign = (keycode == 83 || keycode == 84 || keycode == 85) ? -1 : 1;
	if (keycode == 83 || keycode == 86)
		events->theta->x = (events->theta->x + sign * events->dtheta->x) % 360;
	if (keycode == 84 || keycode == 87)
		events->theta->y = (events->theta->y + sign * events->dtheta->y) % 360;
	if (keycode == 85 || keycode == 88)
		events->theta->z = (events->theta->z + sign * events->dtheta->z) % 360;
	while (++i < img->nb_c * img->nb_l)
	{
		img->p_tab[0][i] = img->i_tab[0][i] + (i % img->nb_c) * events->dst;
		img->p_tab[1][i] = img->i_tab[1][i] + (i / img->nb_c) * events->dst;
		img->p_tab[2][i] = (img->i_tab[2][i] + events->dst) * events->alt;
	}
	ft_rot_xyz(events, img);
	if (ft_center_to_pt(mlx, img, img->center) == 0)
		ft_free_mlx(mlx, 12);
	return (*mlx == NULL ? 0 : 1);
}
