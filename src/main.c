/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:19 by smakni            #+#    #+#             */
/*   Updated: 2019/07/10 02:17:12 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

#define MAX_NOM 1024

void	balayer_rep(char *rep, void (*fcn)(char *))
{
	char			nom[MAX_NOM];
	struct dirent	*pr;
	DIR				*fdr;

	if ((fdr = opendir(rep)) == NULL)
	{
		ft_printf("balayer_rep : impossibe d'ouvrir %s\n", rep);
		return ;
	}
	while ((pr = readdir(fdr))  != NULL)
	{
		if (ft_strcmp(pr->d_name, "..") == 0
			|| ft_strcmp(pr->d_name, ".") == 0)
			continue;
		if (ft_strlen(rep) + ft_strlen(pr->d_name) + 2 > sizeof(nom))
			ft_printf("balayer_rep : nom %s %s trop long\n", rep, pr->d_name);
		else
		{
			ft_sprintf(nom, "%s/%s", rep, pr->d_name);
			(*fcn)(nom);
		}
	}
	closedir(fdr);
}

void	taillef(char *nom)
{
	struct	stat	sttamp;

	if ((stat(nom, &sttamp)) == -1)
	{
		ft_printf("tailled : acces impossible a %s\n", nom);
		return ;
	}
	if (__S_ISTYPE(sttamp.st_mode, __S_IFDIR))
		balayer_rep(nom, taillef);
	ft_printf("%8ld %s\n", sttamp.st_size, nom);
}

int		main(int ac, char **av)
{
	if (ac == 1)
		taillef(".");
	else
		while(--ac > 0)
			taillef(*++av);
    return (0);
}
