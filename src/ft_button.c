/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:11:05 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/29 14:08:39 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "../include/fdf.h"

/*
** FONCTION : POS_BUTTON
** PARAMETRES :	void *init : identifiant de connexion au syst graphique.
** 				t_w_mlx *w_ptr : pointeur sur struct associée à la window.
** 				u-int *but_m :
** 				u-int *but_p :
** DESCRIPTION :
** RETOUR :
*/

void	ft_pos_button(void *init, void *w_ptr, unsigned int *but)
{
	int		nb;
	int		i;
	int		img_y;

	nb = 1;
	i = 8;
	img_y = WIN_LY / 48;
	while (nb < 8)
	{
		mlx_put_image_to_window(init, w_ptr, but, WIN_LX / 142, i * img_y);
		mlx_put_image_to_window(init, w_ptr, but, WIN_LX / 42, i * img_y);
		mlx_string_put(init, w_ptr, WIN_LX / 80, i * img_y, BLANC, "-");
		mlx_string_put(init, w_ptr, WIN_LX / 35, i * img_y, BLANC, "+");
		i = i + 5;
		nb++;
	}
}

/*
** FONCTION : PUT_BUTTON
** PARAMETRES : void *init : identifiant de connexion au syst graphique.
**				void *w_ptr : pointeur sur struct associée à la window.
** DESCRIPTION :
** RETOUR :
** 		0 si pb allocation pr le bouton.
**		1 si tout va bien.
*/

int		ft_put_button(t_mlx *mlx)
{
	t_gdad	gdad;

	if (!(mlx->bouton = (t_img*)malloc(sizeof(t_img))))
		return (0);
	mlx->bouton->ptr = mlx_new_image(mlx->init, 30, 20);
	mlx->bouton->pixels = (unsigned int*)mlx_get_data_addr(mlx->bouton->ptr,
	&gdad.bpp, &gdad.s_l, &gdad.edian);
	ft_fill_field(mlx->bouton->pixels, 30, 20, GRIS_F);
	ft_pos_button(mlx->init, mlx->wind->w_ptr, mlx->bouton->ptr);
	return (1);
}
