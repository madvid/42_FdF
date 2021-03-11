/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_translation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:25:03 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/04 17:26:50 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
** FONCTION : DO_TRANS
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

int		ft_do_trans(int sign, t_events *events, char c)
{
	if (c == 'x')
	{
		if (events->trans_l->x + sign * events->trans_dl->x < -6000
		|| events->trans_l->x + sign * events->trans_dl->x > 6000)
			return (0);
	}
	if (c == 'y')
	{
		if (events->trans_l->y + sign * events->trans_dl->y < -6000
		|| events->trans_l->y + sign * events->trans_dl->y > 6000)
			return (0);
	}
	return (1);
}

/*
** FONCTION : TRANSLATION
** PARAMETRES :	trans_dx : valeur du pas de translation suivant x à appliquer.
**				trans_dy : valeur du pas de translation suivant y à appliquer.
**				*img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Applique la translation suivant x/y à p_tab.
** RETOUR :
**		RIEN.
*/

void	ft_translation(int trans_dx, int trans_dy, t_img *img)
{
	int		i;

	i = -1;
	while (++i < img->nb_c * img->nb_l)
	{
		img->p_tab[0][i] = img->p_tab[0][i] + trans_dx;
		img->p_tab[1][i] = img->p_tab[1][i] + trans_dy;
	}
}

/*
** FONCTION : TRANSLATION
** PARAMETRES :	keycode : valeur de la touche pressée.
**				*events : ptr sur struct contenant toutes les variables
**				relatives aux événements.
**				*img : ptr sur struct contenant toutes les variables
**				relatives à l'image "principale".
** DESCRIPTION :
**		Check si l'event est une translation suivant x ou y et son signe
**		puis applique celle-ci grâce à la fct ft_translation().
** RETOUR :
**		RIEN.
*/

void	ft_event_transl(int keycode, t_events *events, t_img *img)
{
	int		sign;

	sign = (keycode == 123 || keycode == 126) ? -1 : 1;
	if ((keycode == 123 || keycode == 124) && ft_do_trans(sign, events, 'x')
	== 1)
	{
		events->trans_l->x = events->trans_l->x + sign * events->trans_dl->x;
		ft_translation(sign * events->trans_dl->x, 0, img);
		img->center->x = img->center->x + sign * events->trans_dl->x;
	}
	if ((keycode == 125 || keycode == 126) && ft_do_trans(sign, events, 'y')
	== 1)
	{
		events->trans_l->y = events->trans_l->y + sign * events->trans_dl->y;
		ft_translation(0, sign * events->trans_dl->y, img);
		img->center->y = img->center->y + sign * events->trans_dl->y;
	}
}
