/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:35:01 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/30 19:20:50 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <mlx.h>
#include "../include/fdf.h"

/*
**## VERIFICATION DES LEAKS ###
**__attribute__((destructor)) void loop_inf(void){ for(;;); }
*/

/*
** FONCTION : MLX_NEW
** PARAMETRES : p_init : identifiant de connexion au syst graphique.
** 				mlx_eiw : ptr général contenant tous en rapport avec events/img
** 				et wind.
** DESCRIPTION :
**		Permet d'allouer la mémoire pour les structures events/img/wind,
**		nécessaire avant de continuer et faire d'autres actions.
** RETOUR :
**		0 : pb allocation pour wind/events/img.
**		1 : les allocations ont réussit.
*/

int		ft_mlx_new(t_mlx **mlx)
{
	if (!((*mlx)->wind = (t_w_mlx*)malloc(sizeof(t_w_mlx))))
	{
		ft_free_mlx(mlx, 0);
		mlx = NULL;
		return (0);
	}
	if (!((*mlx)->img = (t_img*)malloc(sizeof(t_img))))
	{
		ft_free_mlx(mlx, 1);
		return (0);
	}
	if (!((*mlx)->events = (t_events*)malloc(sizeof(t_events))))
	{
		ft_free_mlx(mlx, 2);
		return (0);
	}
	return (1);
}

/*
** FONCTION : EVENTS_ALLOC
** PARAMETRES : *events : ptr sur struct contenant toutes les variables
** 				relatives aux événements.
** DESCRIPTION :
** 		Allocation des différents objets contenus dans la struct events.
** RETOUR :
** 		0 : s'i 'il y a un pb d'alloctation.
** 		1 : sinon.
*/

int		ft_events_alloc(t_events *events)
{
	if (!(events->middle = (t_fpt*)malloc(sizeof(t_fpt))))
		return (0);
	if (!(events->trans_l = (t_pt*)malloc(sizeof(t_pt))))
	{
		ft_free_events(events, 1);
		return (0);
	}
	if (!(events->trans_dl = (t_pt*)malloc(sizeof(t_pt))))
	{
		ft_free_events(events, 2);
		return (0);
	}
	if (!(events->theta = (t_pt*)malloc(sizeof(t_pt))))
	{
		ft_free_events(events, 3);
		return (0);
	}
	if (!(events->dtheta = (t_pt*)malloc(sizeof(t_pt))))
	{
		ft_free_events(events, 4);
		return (0);
	}
	return (1);
}

/*
** FONCTION : EVENTS_WIND
** PARAMETRES : *mlx : ptr général contenant les struct wind/events/img.
** DESCRIPTION :
**		Initialise les variables relatives à la window et alloue la mémoire pr
**		les objets dans la stuct events.
** RETOUR :
**		-1 : pd d'allocation pr le titre ou dans e
*/

int		ft_events_wind(t_mlx **mlx)
{
	int			w_lx;
	int			w_ly;

	if ((*mlx)->init == NULL)
	{
		free(*mlx);
		return (0);
	}
	(*mlx)->wind->w_lx = (WIN_LX > 2560) ? 2560 : WIN_LX;
	(*mlx)->wind->w_ly = (WIN_LY > 1310) ? 1310 : WIN_LY;
	w_lx = (*mlx)->wind->w_lx;
	w_ly = (*mlx)->wind->w_ly;
	(*mlx)->wind->w_ptr = mlx_new_window((*mlx)->init, w_lx, w_ly, NAME);
	if (((*mlx)->wind->w_title = ft_strdup(NAME)) == NULL)
	{
		ft_free_mlx(mlx, 6);
		return (0);
	}
	if (ft_events_alloc((*mlx)->events) == 0)
	{
		ft_free_mlx(mlx, 7);
		return (0);
	}
	return (1);
}

/*
** FONCTION : FT_CLOSE
** PARAMETRES : *mlx : ptr général contenant les struct wind/events/img.
** DESCRIPTION :
**		Détruit la window et quitte le programme.
** RETOUR :
**		RIEN.
*/

int		ft_close(t_mlx **mlx)
{
	mlx_destroy_image((*mlx)->init, (*mlx)->field[2]->ptr);
	ft_free_mlx(mlx, 13);
	exit(3);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;

	mlx = NULL;
	if (argc != 2)
		ft_putendl("usage: ./fdf [map file], extension '.fdf' is unnecessary");
	if (argc != 2)
		return (0);
	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (0);
	if (ft_mlx_new(&mlx) == 0 || ft_parse(&mlx, mlx->img, argv[1]) == -1)
		return (0);
	mlx->init = mlx_init();
	if (ft_events_wind(&mlx) == 0 || ft_define_field(&mlx) == 0)
		return (0);
	if (ini_events(&mlx, mlx->events, mlx->img) == 0)
		return (0);
	ft_display_map(mlx, mlx->img);
	mlx_hook(mlx->wind->w_ptr, 2, (1L << 0), ft_key_press, &mlx);
	mlx_hook(mlx->wind->w_ptr, 3, (1L << 1), ft_key_release, mlx);
	mlx_mouse_hook(mlx->wind->w_ptr, ft_mouse_event, mlx);
	mlx_hook(mlx->wind->w_ptr, 17, (1L << 17), ft_close, &mlx);
	mlx_loop(mlx->init);
	return (0);
}
