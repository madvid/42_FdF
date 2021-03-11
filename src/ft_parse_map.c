/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:22:10 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/30 18:22:42 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../include/fdf.h"

/*
** FONCTION : FILL_VEC_TAB
** PARAMETRES :	char *s : la string produite à partir du fichier map.
**				t_img img : la struc contenant le tableau et le nb colonnes
** DESCRIPTION :
**		Rempli le tableau contenant l'ensemble des coord des points de la map
**		et duplique le tableau dans p_tab. i_tab ne restera inchangé.
** RETOUR :
**		RIEN.
*/

void	ft_fill(int **i_tab, t_pt xyz, t_pt ij, char *s)
{
	i_tab[0][ij.y] = xyz.x;
	i_tab[1][ij.y] = xyz.y;
	i_tab[2][ij.y] = ft_atoi(&s[ij.x]);
}

/*
** FONCTION : FILL_VEC_TAB
** PARAMETRES :	char *s : la string produite à partir du fichier map.
**				t_img img : la struc contenant le tableau et le nb colonnes
** DESCRIPTION :
**		Rempli le tableau contenant l'ensemble des coord des points de la map
**		et duplique le tableau dans p_tab. i_tab restera inchangé à tt instant.
** RETOUR :
**		-1 : si pb lors allocation de i_tab ou p_tab.
**		0 : si aucun pb.
*/

int		ft_fill_vec_tab(char *s, t_img *img)
{
	static t_pt		xyz;
	static t_pt		ij;

	if (!(img->i_tab = ft_table_int(4, img->nb_c * img->nb_l)))
		return (-2);
	while (s[ij.x])
	{
		while (s[ij.x] == ' ' || s[ij.x] == '\t')
			ij.x++;
		if (ft_isdigit(s[ij.x]) == 1 || (s[ij.x] == '+' || s[ij.x] == '-'))
		{
			ft_fill(img->i_tab, xyz, ij, s);
			ij.y++;
		}
		while (ft_isdigit(s[ij.x]) == 1 || (s[ij.x] == '+' || s[ij.x] == '-'))
			ij.x++;
		xyz.x++;
		if (s[ij.x++] == '\n')
		{
			xyz.x = 0;
			xyz.y++;
		}
	}
	return (((img->p_tab = ft_dbl_tab_dup(img->i_tab, img->nb_c * img->nb_l))
	== NULL) ? -1 : 0);
}

/*
** FONCTION : FILE_TO_STR
** PARAMETRES :	int fd : le filedescriptor du fichier map
**				char **s : la string qui va accueillir le contenue de la map
** DESCRIPTION :
**		Stocke la map dans une chaîne de caractères en retirant les hexa.
** RETOUR :
**		-1 : si le fd est invalide / ou que test_line retourne -1
**		0 : si la map a bien été stockée dans la string s
** REMARQUE : /!\ si la map est infinie
*/

int		ft_file_to_str(int fd, char **s)
{
	char	*l;
	int		s_max;

	s_max = 10000000;
	if (!(l = (char*)malloc(sizeof(char) * s_max)))
	{
		ft_putendl("Error : Do not  succeed to allocate the map.");
		return (-1);
	}
	l[s_max - 1] = '\0';
	if ((read(fd, l, s_max - 1) <= 0) || (ft_trunc_hexa(&l)) == NULL
	|| (ft_test_line(l) == -1))
	{
		ft_strdel(&l);
		return (-1);
	}
	if ((*s = ft_strdup(l)) == NULL)
	{
		ft_strdel(&l);
		return (-1);
	}
	ft_strdel(&l);
	return (1);
}

/*
** FONCTION : PARSE_MAP
** PARAMETRES : *img : ptr sur struct contenant toutes les variables relatives
**				à l'image "principale".
**				char *file : nom du fichier à parser (hypothétiquement le map).
** DESCRIPTION :
**		Fonction orchestrant le parsing de la map.
** RETOUR :
**		-1 : si la map est invalide.
**		0 : si la map est valide.
*/

int		ft_parse(t_mlx **mlx, t_img *img, char *file)
{
	char	*str;
	int		fd;
	int		err;

	str = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 3 || ft_file_to_str(fd, &str) == -1)
	{
		ft_putendl("Map is invalid or does not exist or cannot be stored.");
		ft_strdel(&str);
		close(fd);
		ft_free_mlx(mlx, 3);
		return (-1);
	}
	img->nb_c = ft_count_nbr(str, "colonne");
	img->nb_l = ft_count_nbr(str, "ligne");
	if ((err = ft_fill_vec_tab(str, img)) < 0)
	{
		ft_strdel(&str);
		close(fd);
		ft_free_mlx(mlx, 5 + err);
		return (-1);
	}
	ft_strdel(&str);
	return (close(fd) + 1);
}
