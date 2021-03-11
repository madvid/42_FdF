/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 22:27:06 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/30 18:29:09 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include "../include/fdf.h"

/*
** FONCTION : FREE_MLX_PART2 & FREE_MLX
** PARAMETRES :	*mlx_eiw : ptr sur struct contenant toutes les variables
** 				relatives à wind/events/img.
** 				option : int permettant de savoir quels objets sontt à libérer.
** DESCRIPTION :
** 		Libère les objets précédemment alloués dans la struct mlx_eiw.
** RETOUR :
** 		RIEN.
*/

void	ft_free_mlx_part2(t_mlx **mlx, int option)
{
	if (option >= 8 && option != 11 && option != 12 && option != 13)
		ft_free_events((*mlx)->events, 5);
	if (option >= 7)
		free((*mlx)->wind->w_title);
	if (option >= 6)
		mlx_destroy_window((*mlx)->init, (*mlx)->wind->w_ptr);
	if (option >= 5)
		ft_free_tabdbl((*mlx)->img->p_tab, 3);
	if (option >= 4)
		ft_free_tabint((*mlx)->img->i_tab, 4);
	if (option >= 3)
		free((*mlx)->events);
	if (option >= 2)
		free((*mlx)->img);
	if (option >= 1)
		free((*mlx)->wind);
	free(*mlx);
	*mlx = NULL;
}

void	ft_free_mlx(t_mlx **mlx, int option)
{
	if (option >= 13)
		free((*mlx)->img->center);
	if (option >= 11)
		ft_free_events((*mlx)->events, option - 5);
	if (option >= 10)
	{
		mlx_destroy_image((*mlx)->init, (*mlx)->bouton->ptr);
		free((*mlx)->bouton);
	}
	if (option >= 9)
	{
		mlx_destroy_image((*mlx)->init, (*mlx)->field[0]->ptr);
		mlx_destroy_image((*mlx)->init, (*mlx)->field[1]->ptr);
		free((*mlx)->field[0]);
		free((*mlx)->field[1]);
		free((*mlx)->field[2]);
		free((*mlx)->field);
	}
	ft_free_mlx_part2(mlx, option);
}

/*
** FONCTION : FREE_EVENTS
** PARAMETRES :	*events : ptr sur struct contenant toutes les variables
** 				relatives aux événements.
** 				option : entier permettant de savoir quels objets à libérer.
** DESCRIPTION :
** 		Libère les objets précédemment alloués dans la struct events.
** RETOUR :
** 		RIEN.
*/

void	ft_free_events(t_events *events, int option)
{
	if (option >= 1)
		free(events->middle);
	if (option >= 2)
		free(events->trans_l);
	if (option >= 3)
		free(events->trans_dl);
	if (option >= 4)
		free(events->theta);
	if (option >= 5)
		free(events->dtheta);
	if (option >= 6)
		ft_free_tabdbl(events->m_iso, 3);
	if (option >= 7)
		ft_free_tabdbl(events->m_cabinet, 3);
}
