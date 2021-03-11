/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:15:17 by mdavid            #+#    #+#             */
/*   Updated: 2019/09/30 18:08:31 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/fdf.h"

/*
** FONCTION : SKIP_SPACE_AND_SIGN
** PARAMETRES :	char *s : chaîne de caractères.
**				int *i : index relatives à la position au sein de la chaîne s.
** DESCRIPTION :
**		Fonction qui permet de passer les espaces les tabultations et les signes
**		au sein de la chaîne.
** RETOUR :
**		RIEN.
*/

void	ft_skip_space_and_sign(char *s, int *i)
{
	while ((s[*i] == ' ' || s[*i] == '\t' || s[*i] == '-' || s[*i] == '+')
	&& s[*i])
		*i = *i + 1;
}

/*
** FONCTION : SKIP_NUMBER
** PARAMETRES :	char *s : chaîne de caractères.
**				int *i : index relatives à la position au sein de la chaîne s.
**				int *nb : compteur de nombre au sein de la chaîne *s.
** DESCRIPTION :
**		Dénombre les nombres au sein de la chaîne *s et stocke ce compte dans
**		la variable nb.
** RETOUR :
**		RIEN.
*/

void	ft_skip_number(char *s, int *i, int *nb)
{
	if (s[*i] >= '0' && s[*i] <= '9' && s[*i])
		*nb = *nb + 1;
	while (s[*i] >= '0' && s[*i] <= '9' && s[*i])
		*i = *i + 1;
}

/*
** FONCTION : COUNT_NBR
** PARAMETRES : char *s : la string contenant tout le fichier *.fdf
**				char *option : [="colonne"/"ligne"].
** DESCRIPTION :
**		Permet de denombrer le nombre de ligne ou de colonne (en fct de option)
**		dans le fichier correspondant à la map.
** RETOUR :
**		0	: si file est vide.
**		nb	: le nb de colonne de la ligne.
**		lign :	le nb de ligne au sein du fichier.
*/

int		ft_count_nbr(char *s, char *option)
{
	int			nb;
	int			i;
	static int	lign;

	nb = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		ft_skip_space_and_sign(s, &i);
		ft_skip_number(s, &i, &nb);
		if (s[i] == '\n' || s[i] == '\0')
		{
			i++;
			if (ft_strcmp(option, "colonne") == 0)
				return (nb);
			lign++;
		}
	}
	if (ft_strcmp(option, "ligne") == 0)
		return (lign);
	return (-1);
}

/*
** FONCTION : CHECK_EACH_C
** PARAMETRES : char *s : line representant la map.
**				int  ref : valeur de reference pr le nb de colonnes
** DESCRIPTION :
**		Vérifie que le nombre de colonnes est strictement identique
**		pour toutes les lignes
** RETOUR :
**		0/-1 :	le nb de colonnes de l'ensemble des lignes [est]/
**				[n'est pas] identique.
*/

int		ft_check_each_c(char *s, int ref)
{
	int		nb_c;
	int		i;

	i = 0;
	while (s[i])
	{
		nb_c = 0;
		while (s[i] != '\n' && s[i] != '\0')
		{
			ft_skip_space_and_sign(s, &i);
			ft_skip_number(s, &i, &nb_c);
		}
		if (nb_c != ref)
			return (-1);
		if (s[i] != '\0')
			i++;
	}
	return (0);
}

/*
** FONCTION : TEST_LINE
** PARAMETRES : char *line : line représentant la map.
** DESCRIPTION :
**		Vérifie que la ligne contient uniquement des espaces (' '/'\t')
**		des signes ('+'/'-'), des retours à la ligne et des nb.
** RETOUR :
*/

int		ft_test_line(char *l)
{
	int			i;
	static int	nb_c;

	i = 0;
	while (l[i])
	{
		while (l[i] == ' ' || l[i] == '\t')
			i++;
		if ((l[i] == '-' || l[i] == '+' || l[i] == '\n'))
			i++;
		while (l[i] && ft_isdigit(l[i]) == 1)
			i++;
		if (l[i] && l[i] != '-' && l[i] != '+' && (ft_isdigit(l[i]) == 0
		&& l[i] != ' ' && l[i] != '\t' && l[i] != '\n'))
			return (-1);
		if (l[i] == '\0')
			break ;
	}
	nb_c = ft_count_nbr(l, "colonne");
	if (ft_check_each_c(l, nb_c) == -1)
		return (-1);
	return (nb_c);
}
