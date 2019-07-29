/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 14:40:23 by smakni            #+#    #+#             */
/*   Updated: 2019/07/29 16:10:50 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	print_data(t_env *env)
{
	int i;

	i = 0;
	alphaqsort_data(env->data, 0, env->nb_files - 1);
	if (env->opt & T)
		qsort_data(env->data, 0, env->nb_files - 1);
	if (env->opt & SR)
	{
		i = env->nb_files - 1;
		while (i >= 0)
			ft_printf("%s", env->data[i--].output);
	}
	else
		while (i < env->nb_files)
			ft_printf("%s", env->data[i++].output);
}

void	print_path(t_env *env, char *path)
{
	if (env->cursor > 0)
		ft_putendl("");
	if (env->nb_files > 0 && env->cursor > 0)
		ft_printf("%s:\n", path);
	else if (env->cursor > 0)
		ft_printf("%s\n", path);
}
