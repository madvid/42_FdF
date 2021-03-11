/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_definition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:56:42 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/29 15:01:26 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <mlx.h>
#include "../include/fdf.h"

/*
** FONCTION : FILL_FIELD
** PARAMETRES : u- int *pixels : chaîne de pixels correspondant à l'image.
**				int width : largeur de l'image.
**				int height : hauteur de l'image.
**				int color : valeur en int de la couleur à mettre sur le pixel.
** DESCRIPTION :
**		Remplie entièrement l'image à la couleur souhaitée.
** RETOUR :
**		RIEN.
*/

void	ft_fill_field(unsigned int *pixels, int width, int height, int color)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < width * height)
	{
		pixels[i % width + i / width * width] = color;
		j++;
	}
}

/*
** FONCTION : FIELD_ALLOCATION
** PARAMETRES : RIEN
** DESCRIPTION :
**		Retourne un tableau de 3 éléments de type t_img pour traiter les champs
**		autour de l'image qui contient la map.
** RETOUR :
**		0 : s'il y a un pb d'allocation pour field.
**		t_img **field : le tableau relatif aux images constituants les champs
**		autour de l'img de la map.
*/

t_img	**ft_field_allocation(void)
{
	t_img	**field;
	int		i;

	i = 0;
	if (!(field = (t_img**)malloc(sizeof(t_img*) * 3)))
		return (NULL);
	while (i < 3)
	{
		if (!(field[i] = (t_img*)malloc(sizeof(t_img))))
		{
			while (--i > 0)
				free(field[i]);
			free(field);
			field = NULL;
			return (NULL);
		}
		i++;
	}
	return (field);
}

/*
** FONCTION : PUT_TEXT_PARAMETERS
** PARAMETRES :	t_mlx *mlx : ptr général contenant les struct wind/events/img.
**				void *init : identifiant de connexion au syst graphique.
**				void *w_ptr : pointeur sur struct associée à la window.
** DESCRIPTION :
**		Place les textes concernant le champ à gauche de la fenêtre.
** RETOUR :
**		0/1.
*/

int		ft_put_text_parameters(t_mlx *mlx, void *init, void *w_ptr)
{
	int		w_lx;
	int		w_ly;

	w_lx = WIN_LX / 144;
	w_ly = WIN_LY / 48;
	mlx_string_put(init, w_ptr, w_lx, 6 * w_ly, NOIR, " a(x) =");
	mlx_string_put(init, w_ptr, w_lx, 7 * w_ly, NOIR, "da(x) =");
	mlx_string_put(init, w_ptr, w_lx, 11 * w_ly, NOIR, " a(y) =");
	mlx_string_put(init, w_ptr, w_lx, 12 * w_ly, NOIR, "da(y) =");
	mlx_string_put(init, w_ptr, w_lx, 16 * w_ly, NOIR, " a(z) =");
	mlx_string_put(init, w_ptr, w_lx, 17 * w_ly, NOIR, "da(z) =");
	mlx_string_put(init, w_ptr, w_lx, 21 * w_ly, NOIR, " T(x) =");
	mlx_string_put(init, w_ptr, w_lx, 22 * w_ly, NOIR, "dT(x) =");
	mlx_string_put(init, w_ptr, w_lx, 26 * w_ly, NOIR, " T(y) =");
	mlx_string_put(init, w_ptr, w_lx, 27 * w_ly, NOIR, "dT(y) =");
	mlx_string_put(init, w_ptr, w_lx, 31 * w_ly, NOIR, " 10.h =");
	mlx_string_put(init, w_ptr, w_lx, 32 * w_ly, NOIR, "10.dh =");
	mlx_string_put(init, w_ptr, w_lx, 36 * w_ly, NOIR, " Zoom =");
	mlx_string_put(init, w_ptr, w_lx, 37 * w_ly, NOIR, "dZoom =");
	if (ft_put_button(mlx) == 0)
		return (0);
	return (1);
}

/*
** FONCTION : PUT_TEXT_CMD
** PARAMETRES : void *init : identifiant de connexion au syst graphique.
**				void *w_ptr : pointeur sur struct associée à la window.
** DESCRIPTION :
**		Place le texte concernant la liste des commandes.
** RETOUR :
**		RIEN.
*/

void	ft_put_text_cmd(void *init, void *w_ptr)
{
	int		lx;
	int		ly;

	lx = WIN_LX / 24;
	ly = WIN_LY / 144;
	mlx_string_put(init, w_ptr, 12 * lx, ly, NOIR, "LIST OF COMMANDS :");
	mlx_string_put(init, w_ptr, 2 * lx, 3 * ly, BLANC, "Rotation a(x) : 1 | 4");
	mlx_string_put(init, w_ptr, 2 * lx, 6 * ly, BLANC, "Rotation a(y) : 2 | 5");
	mlx_string_put(init, w_ptr, 2 * lx, 9 * ly, BLANC, "Rotation a(z) : 3 | 6");
	mlx_string_put(init, w_ptr, 6 * lx, 3 * ly, BLANC,
	"Translation x : Left | Right");
	mlx_string_put(init, w_ptr, 6 * lx, 6 * ly, BLANC,
	"Translation y : Up | Down");
	mlx_string_put(init, w_ptr, 6 * lx, 9 * ly, BLANC,
	"Elevation z : (-/_) | (=/+)");
	mlx_string_put(init, w_ptr, 10 * lx, 3 * ly, BLANC, "Zoom -/+ : - | +");
	mlx_string_put(init, w_ptr, 10 * lx, 6 * ly, BLANC, "Projection iso : i");
	mlx_string_put(init, w_ptr, 10 * lx, 9 * ly, BLANC,
	"Projection parrallele : p");
}

/*
** FONCTION : DEFINE_FIELD
** PARAMETRES : t_mlx *mlx : ptr général contenant les struct wind/events/img.
** DESCRIPTION :
**		Gère l'allocation et l'affichage des champs permanents autour de
**		l'image.
** RETOUR :
**		RIEN.
*/

int		ft_define_field(t_mlx **mlx)
{
	t_img		**field;
	t_gdad		gdad;

	if (!(field = ft_field_allocation()))
	{
		ft_free_mlx(mlx, 8);
		return (0);
	}
	field[0]->ptr = mlx_new_image((*mlx)->init, WIN_LX, WIN_LY / 12);
	field[1]->ptr = mlx_new_image((*mlx)->init, WIN_LX / 22, 21 * WIN_LY / 24);
	field[0]->pixels = (unsigned int*)mlx_get_data_addr(field[0]->ptr,
	&gdad.bpp, &gdad.s_l, &gdad.edian);
	field[1]->pixels = (unsigned int*)mlx_get_data_addr(field[1]->ptr,
	&gdad.bpp, &gdad.s_l, &gdad.edian);
	ft_fill_field(field[0]->pixels, WIN_LX, WIN_LY / 12, GRIS_F);
	ft_fill_field(field[1]->pixels, WIN_LX / 22, 21 * WIN_LY / 24, GRIS);
	(*mlx)->field = field;
	mlx_put_image_to_window((*mlx)->init, (*mlx)->wind->w_ptr, field[0]->ptr, 0,
	0);
	mlx_put_image_to_window((*mlx)->init, (*mlx)->wind->w_ptr, field[1]->ptr, 0,
	WIN_LY / 12);
	ft_put_text_cmd((*mlx)->init, (*mlx)->wind->w_ptr);
	if (ft_put_text_parameters(*mlx, (*mlx)->init, (*mlx)->wind->w_ptr) == 0)
		ft_free_mlx(mlx, 9);
	return (mlx == NULL ? 0 : 1);
}
