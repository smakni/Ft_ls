/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:02:19 by marvin            #+#    #+#             */
/*   Updated: 2019/07/16 15:50:14 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		swap_data(t_env *env)
{
	int		i;
	t_data	tmp;

	i = 0;
	while (i < env->nb_files)
	{
		if (env->data[i].time < env->data[i + 1].time && i + 1 < env->nb_files)
		{
			tmp = env->data[i];
			env->data[i] = env->data[i + 1];
			env->data[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}
