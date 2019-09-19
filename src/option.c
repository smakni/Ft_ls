/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:00:34 by smakni            #+#    #+#             */
/*   Updated: 2019/09/19 15:03:18 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		option(char *av, char *opt)
{
	if (ft_strcmp(av, "--") == 0)
		return ;
	av++;
	while(*av)
	{
		if (*av == 'R')
			*opt |= 1;
		else if (*av == 'l')
			*opt |= 2;
		else if (*av == 'a')
			*opt |= 4;
		else if (*av == 'r')
			*opt |= 8;
		else if (*av == 't')
			*opt |= 16;
		else if (*av == '1')
			*opt |= 32;
		else
		{
			ft_printf("/bin/ls: illegal option -- %c\n", *av);
			ft_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
			exit (1);
		}
		av++;
	}
}
