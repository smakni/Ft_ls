/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:49:51 by smakni            #+#    #+#             */
/*   Updated: 2019/07/24 23:38:18 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		save_output(t_env *env)
{
	int			i;
	int			ret;
	char		*time;

	i = 0;
	while (i < env->nb_files)
	{
		ret = env->max_width.perm;
		if (env->opt & L)
		{
			time = ctime((time_t *)&env->data[i].time);
			ret += env->max_width.l - env->data[i].width.l + 1;
			ret += ft_sprintf(&env->data[i].output[ret], "%d", env->data[i].nb_link);
			env->data[i].output[ret] = ' ';
			ret += env->max_width.un - env->data[i].width.un + 1;
			ret += ft_sprintf(&env->data[i].output[ret], "%s", env->data[i].pw_name);
			env->data[i].output[ret] = ' ';
			ret += env->max_width.gn - env->data[i].width.gn + 1;
			ret += ft_sprintf(&env->data[i].output[ret], "%s", env->data[i].gr_name);
			env->data[i].output[ret] = ' ';
			ret += env->max_width.s - env->data[i].width.s + 1;
			ret += ft_sprintf(&env->data[i].output[ret], "%u ", env->data[i].st_size);
			ret += ft_sprintf(&env->data[i].output[ret], "%.12s ", &time[4]);
		}
		if (env->data[i].output[0] == 'l' && (env->opt & L))
			ret += ft_sprintf(&env->data[i].output[ret], "%s -> %s\n",
				env->data[i].f_name, link);
		else
			ret += ft_sprintf(&env->data[i].output[ret], "%s\n",
											env->data[i].f_name);
		i++;
	}
	ft_bzero(&env->max_width, sizeof(t_width));
	return (ret);
}
