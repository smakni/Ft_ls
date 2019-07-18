/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:06:57 by sabri             #+#    #+#             */
/*   Updated: 2019/07/18 12:18:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	realloc_tab(t_env *env)
{
	t_data			*tmp;
	int				i;

	i = 0;
	env->capacity *= 2;
	ft_printf("reaLLOC\n");
	if (!(tmp = ft_memalloc(sizeof(t_data) * (env->capacity))))
	{
		ft_memdel((void *)&env->data);
		return (-1);
	}
	while (i < env->nb_files)
	{
		tmp[i] = env->data[i];
		i++;
	}
	free(env->data);
	env->data = tmp;
	return (0);
}
