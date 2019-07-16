/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:02:19 by marvin            #+#    #+#             */
/*   Updated: 2019/07/15 13:02:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	swap_data(t_env *env)
{
	int i;
	t_data tmp;

	i = 0;
	while (i < env->nb_files)
	{
		//ft_printf("%s < %s ? \n", env->data[i].f_name, env->data[i + 1].f_name);
		if (env->data[i].time < env->data[i + 1].time && i + 1 < env->nb_files)
		{
			//ft_printf("yes\n");
			tmp = env->data[i];
			env->data[i] = env->data[i + 1];
			env->data[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}
