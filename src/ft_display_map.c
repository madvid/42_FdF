/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:04:11 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/11 19:11:07 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include "../include/fdf.h"

/*
** FONCTION : STR_PUT
** PARAMETRES : t_mlx mlx_iniwin
** DESCRIPTION :
**		...
** RETOUR :
**		...
*/

void	ft_str_put(t_mlx *mlx, int x, int y, int param)
{
	char	*s;

	s = ft_itoa(param);
	mlx_string_put(mlx->init, mlx->wind->w_ptr, x, y, NOIR, s);
	free(s);
}

/*
** FONCTION : STRINGS_PARAM
** PARAMETRES : t_mlx mlx_iniwin
** DESCRIPTION :
**		...
** RETOUR :
**		...
*/

void	ft_strings_param(t_mlx *mlx, t_events *events)
{
	int		x;
	int		y;

	x = WIN_LX / 20;
	y = WIN_LY / 48;
	ft_str_put(mlx, x, 6 * y, (int)(events->theta->x));
	ft_str_put(mlx, x, 7 * y, (int)(events->dtheta->x));
	ft_str_put(mlx, x, 11 * y, (int)(events->theta->y));
	ft_str_put(mlx, x, 12 * y, (int)(events->dtheta->y));
	ft_str_put(mlx, x, 16 * y, (int)(events->theta->z));
	ft_str_put(mlx, x, 17 * y, (int)(events->dtheta->z));
	ft_str_put(mlx, x, 21 * y, (int)(events->trans_l->x));
	ft_str_put(mlx, x, 22 * y, (int)(events->trans_dl->x));
	ft_str_put(mlx, x, 26 * y, (int)(events->trans_l->y));
	ft_str_put(mlx, x, 27 * y, (int)(events->trans_dl->y));
	ft_str_put(mlx, x, 31 * y, (int)(10 * events->alt));
	ft_str_put(mlx, x, 32 * y, (int)(10 * events->d_alt));
	ft_str_put(mlx, x, 36 * y, (int)(events->dst));
	ft_str_put(mlx, x, 37 * y, (int)(events->d_dst));
}

/*
** FONCTION : DISPLAY_MAP
** PARAMETRES : t_mlx mlx_iniwin
** DESCRIPTION :
**		...
** RETOUR :
**		...
*/

void	ft_put_parameter_bar(t_mlx *mlx, t_img **field)
{
	t_gdad		gdad;

	field[2]->ptr = mlx_new_image(mlx->init, WIN_LX / 22, 21 * WIN_LY / 24);
	field[2]->pixels = (unsigned int*)mlx_get_data_addr(field[2]->ptr
	, &gdad.bpp, &gdad.s_l, &gdad.edian);
	ft_fill_field(field[2]->pixels, WIN_LX / 22, 21 * WIN_LY / 24, GRIS);
	mlx_put_image_to_window(mlx->init, mlx->wind->w_ptr, field[2]->ptr
	, WIN_LX / 24, WIN_LY / 12);
	ft_strings_param(mlx, mlx->events);
}

/*
** FONCTION : DISPLAY_MAP
** PARAMETRES : t_mlx mlx_iniwin
** DESCRIPTION :
**		...
** RETOUR :
**		...
*/

int		ft_draw(t_img *img)
{
	int		px;
	int		py;
	int		i;

	i = -1;
	while (++i < img->nb_c * img->nb_l)
	{
		px = (int)round(img->p_tab[0][i]);
		py = IMG_LX * (int)round(img->p_tab[1][i]);
		add_pixel(px, py, img, img->i_tab[3][i]);
	}
	return (0);
}

/*
** FONCTION : DISPLAY_MAP
** PARAMETRES : t_mlx mlx
** DESCRIPTION :
**		...
** RETOUR :
**		...
*/

int		ft_display_map(t_mlx *mlx, t_img *img)
{
	t_gdad		gdad;

	img->ptr = mlx_new_image(mlx->init, 11 * WIN_LX / 12, 22 * WIN_LY / 24);
	img->pixels = (unsigned int*)mlx_get_data_addr(img->ptr, &gdad.bpp,
		&gdad.s_l, &gdad.edian);
	ft_draw(img);
	link_points(img->nb_c, img->nb_l, img);
	mlx_put_image_to_window(mlx->init, mlx->wind->w_ptr, img->ptr, WIN_LX / 12
	, WIN_LY / 12);
	ft_put_parameter_bar(mlx, mlx->field);
	return (0);
}
