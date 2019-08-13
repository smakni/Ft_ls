/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:02:19 by marvin            #+#    #+#             */
/*   Updated: 2019/08/13 12:21:39 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		swap_data(t_env *e)
{
	int		i;
	t_data	tmp;

	i = e->nb_files;
	ft_printf("swap\n");
	while (i - 1 >= 0 && e->data[i].time >= e->data[i - 1].time)
	{
		ft_printf("i = %s > i - 1 = %s\n", e->data[i].f_name, e->data[i - 1].f_name);
		tmp = e->data[i];
		e->data[i] = e->data[i - 1];
		e->data[i - 1] = tmp;
		i--;
	}
}

void		swap_dir(t_path_r *path_r)
{
	int			i;
	t_path		tmp;

	i = 0;
	while (i < path_r->nb_path)
	{
		if (path_r->path_lst[i].time < path_r->path_lst[i + 1].time && i + 1 < path_r->nb_path)
		{
			tmp = path_r->path_lst[i];
			path_r->path_lst[i] = path_r->path_lst[i + 1];
			path_r->path_lst[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}
