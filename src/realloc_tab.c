/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:06:57 by sabri             #+#    #+#             */
/*   Updated: 2019/09/19 10:54:47 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	realloc_tab(t_env *e)
{
	t_data			*tmp;
	int				i;

	i = 0;
	e->capacity *= 2;
	if (!(tmp = ft_memalloc(sizeof(t_data) * (e->capacity))))
	{
		ft_memdel((void *)&e->data);
		return (-1);
	}
	while (i < e->nb_files)
	{
		tmp[i] = e->data[i];
		i++;
	}
	free(e->data);
	e->data = tmp;
	return (0);
}
