/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 19:09:28 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/04 17:26:15 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include "../include/fdf.h"

/*
** FONCTION : KEY_PRESS
** PARAMETRES :	int keycode : valeur de la touche du clavier pressée.
**				t_mlx *mlx : ptr général contenant les struct wind/events/img.
** DESCRIPTION :
**		Gère les événements liés au clavier.
** RETOUR :
**		0 : Aucune gestion de la valeur de retour, le prototype impose un int
**			en retour de la fct.
*/

int		ft_key_press(int keycode, t_mlx **mlx)
{
	mlx_destroy_image((*mlx)->init, (*mlx)->img->ptr);
	if (keycode == 53)
		ft_close(mlx);
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
		ft_event_transl(keycode, (*mlx)->events, (*mlx)->img);
	if (keycode >= 83 && keycode <= 88)
		ft_rotation_xyz(keycode, mlx, (*mlx)->events, (*mlx)->img);
	if (keycode == 24 || keycode == 27)
		ft_altitude(keycode, mlx, (*mlx)->events, (*mlx)->img);
	if (keycode == 69 || keycode == 78)
		ft_zoom(keycode, mlx, (*mlx)->events, (*mlx)->img);
	if (keycode == 34 || keycode == 35)
		ft_projections(keycode, mlx, (*mlx)->events, (*mlx)->img);
	ft_display_map(*mlx, (*mlx)->img);
	return (0);
}

/*
** FONCTION : KEY_RELEASE
** PARAMETRES : t_mlx *mlx : ptr général contenant les struct wind/events/img.
** DESCRIPTION :
**		Aucune gestion particulière lors du relâchement des touches, mais
**		nécessaire pour gérer les actions répétées si on maintien une touche.
** RETOUR :
**		0 : Aucune gestion de la valeur de retour, le prototype impose un int
**			en retour de la fct.
*/

int		ft_key_release(int keycode, t_mlx *mlx)
{
	if (keycode)
		(void)mlx;
	return (0);
}

/*
** FONCTION : DEAL_PRESS_BUTTON
** PARAMETRES :	int nu :
** 				int sign :
** 				t_mlx *mlx : ptr général contenant les struct wind/events/img.
** 				t_events *events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
** DESCRIPTION :
**		Gère la modification du paramètre associé au bouton sur lequel on clic.
** RETOUR :
**		RIEN.
*/

void	ft_deal_press_button(int nu, int sign, t_mlx *mlx, t_events *events)
{
	if (nu == 1 && events->dtheta->x + 2 * sign > 0)
		events->dtheta->x = (events->dtheta->x % 360) + 2 * sign;
	if (nu == 2 && events->dtheta->y + 2 * sign > 0)
		events->dtheta->y = (events->dtheta->y % 360) + 2 * sign;
	if (nu == 3 && events->dtheta->z + 2 * sign > 0)
		events->dtheta->z = (events->dtheta->z % 360) + 2 * sign;
	if (nu == 4 && events->trans_dl->x + sign * 2 > 2
	&& events->trans_dl->x + sign * 2 < 100)
		events->trans_dl->x = events->trans_dl->x + sign * 2;
	if (nu == 5 && events->trans_dl->y + sign * 2 > 2
	&& events->trans_dl->y + sign * 2 < 100)
		events->trans_dl->y = events->trans_dl->y + sign * 2;
	if (nu == 6 && events->d_alt + sign * 0.2 > 0
	&& events->d_alt + sign * 0.2 < 25)
		events->d_alt = events->d_alt + sign * 0.1;
	if (nu == 7 && events->d_dst + sign * 2 > 0
	&& events->d_dst + sign * 2 < 10)
		events->d_dst = events->d_dst + sign * 2;
	ft_put_parameter_bar(mlx, mlx->field);
}

/*
** FONCTION : MOUSE_EVENT
** PARAMETRES :	int keycode : valeur de la touche de la souris pressée.
**				t_mlx *mlx : ptr général contenant les struct wind/events/img.
** DESCRIPTION :
**		Gère les événements liés à la souris.
** RETOUR :
**		0 : Aucune gestion de la valeur de retour, le prototype impose un int
**			en retour de la fct.
*/

int		ft_mouse_event(int button, int x, int y, t_mlx *mlx)
{
	int		sign;
	int		nu;
	int		i;

	sign = 0;
	nu = 1;
	i = 8;
	if (button == 1)
	{
		if (x >= WIN_LX / 142 && x <= WIN_LX / 142 + 30)
			sign = -1;
		if (x >= WIN_LX / 42 && x <= WIN_LX / 42 + 30)
			sign = 1;
		while (nu < 8)
		{
			if (sign != 0 && (y >= i * WIN_LY / 48 && y <= i * WIN_LY / 48
			+ 20))
				break ;
			i = i + 5;
			nu++;
		}
		if (sign != 0 && nu != 8)
			ft_deal_press_button(nu, sign, mlx, mlx->events);
	}
	return (0);
}
