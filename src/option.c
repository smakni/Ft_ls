/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:00:34 by smakni            #+#    #+#             */
/*   Updated: 2019/07/25 15:34:52 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		option(char *av, char *opt)
{
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
		else
		{
			ft_printf("/bin/ls: illegal option -- %c\n", *av);
			ft_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
			exit (1);
		}
		av++;
	}
}
