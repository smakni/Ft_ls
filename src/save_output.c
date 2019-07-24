/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:49:51 by smakni            #+#    #+#             */
/*   Updated: 2019/07/24 19:35:12 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		save_output(t_env *env)
{
	int			i;
	int			ret;
	char		*time;

	i = 0;
	ft_printf("perm = %d | l = %d | un = %d | gn = %d | s = %d\n",
			env->max_width.perm, env->max_width.l, env->max_width.un, env->max_width.gn, env->max_width.s);
	while (i < env->nb_files)
	{
		ret = env->max_width.perm;
		if (env->opt & L) //remplacer les width avec les max ans t_width
		{
			ft_printf("%u\n", env->data[i].st_size);
			time = ctime((time_t *)&env->data[i].time);
			ret += env->max_width.l - env->data[i].width.l + 1;
			ret += ft_sprintf(&env->data[i].output[ret], "%d ", env->data[i].nb_link);
			ret += env->max_width.un - env->data[i].width.un;
			ret += ft_sprintf(&env->data[i].output[ret], "%s ", env->data[i].pw_name);
			ret += env->max_width.gn - env->data[i].width.gn;
			ret += ft_sprintf(&env->data[i].output[ret], "%s ", env->data[i].gr_name);
			// ret += env->max_width.s - env->data[i].width.s;
			// ret += ft_sprintf(&env->data[i].output[ret], "%u ", env->data[i].st_size);
			ret += ft_sprintf(&env->data[i].output[ret], "%.12s ", &time[4]);
		}
		if (env->data[i].output[0] == 'l' && (env->opt & L))
			ret += ft_sprintf(&env->data[i].output[ret], "%s -> %s\n",
				env->data[i].f_name, link);
		else
			ret += ft_sprintf(&env->data[i].output[ret], "%s\n",
											env->data[i].f_name);
		//env->data[i].output[ret] = '@';
		//env->data[i].output[ret + 1] = '\0';
		i++;
	}
	ft_bzero(&env->max_width, sizeof(t_width));
	return (ret);
}
