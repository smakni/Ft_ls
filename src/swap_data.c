/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:02:19 by marvin            #+#    #+#             */
/*   Updated: 2019/09/18 18:13:42 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		swap_data(t_env *e)
{
	int		i;
	t_data	tmp;

	i = e->nb_files;
	if (e->opt & T)
	{
		// ft_printf("LOOP[%s]\n", e->data[i].f_name);
		while (i - 1 >= 0 && e->data[i].time > e->data[i - 1].time)
		{
			// ft_printf("DIFF_TIME[%s]-[%s]=%d\n", e->data[i].f_name, e->data[i - 1].f_name, e->data[i].time - e->data[i - 1].time);
			tmp = e->data[i];
			e->data[i] = e->data[i - 1];
			e->data[i - 1] = tmp;
			i--;
		}
		while (i - 1 >= 0 && e->data[i].time == e->data[i - 1].time
		&& ft_strcmp(e->data[i].f_name, e->data[i - 1].f_name) > 0)
		{
			// ft_printf("DIFF_NAME[%s]-[%s]=%d\n", e->data[i].f_name, e->data[i - 1].f_name, ft_strcmp(e->data[i].f_name, e->data[i - 1].f_name));
			tmp = e->data[i];
			e->data[i] = e->data[i - 1];
			e->data[i - 1] = tmp;
			i--;
		}
	}
	else
	{	
		while (i - 1 >= 0
		&& ft_strcmp(e->data[i].f_name, e->data[i - 1].f_name) < 0)
		{
			tmp = e->data[i];
			e->data[i] = e->data[i - 1];
			e->data[i - 1] = tmp;
			i--;
		}
	}
	// i = 0;
	// ft_printf("________________\n");
	// while (i <= e->nb_files)
	// 	ft_printf("%s\n", e->data[i++].f_name);
	// ft_printf("________________\n");
}

void		swap_dir(t_env *e, t_path_r *path_r)
{
	int			i;
	t_path		tmp;

	i = path_r->nb_path;
	if (e->opt & T)
	{
		while (i - 1 >= 0 
		&& path_r->path_lst[i].time > path_r->path_lst[i - 1].time)
		{
			tmp = path_r->path_lst[i];
			path_r->path_lst[i] = path_r->path_lst[i - 1];
			path_r->path_lst[i - 1] = tmp;
			i--;
		}
		while (i - 1 >= 0 
		&& path_r->path_lst[i].time == path_r->path_lst[i - 1].time
		&& ft_strcmp(path_r->path_lst[i].path, path_r->path_lst[i - 1].path) > 0)
		{
			tmp = path_r->path_lst[i];
			path_r->path_lst[i] = path_r->path_lst[i - 1];
			path_r->path_lst[i - 1] = tmp;
			i--;
		}
	}
	else
	{
		while (i - 1 >= 0
		&& ft_strcmp(path_r->path_lst[i].path, path_r->path_lst[i - 1].path) < 0)
		{
			tmp = path_r->path_lst[i];
			path_r->path_lst[i] = path_r->path_lst[i - 1];
			path_r->path_lst[i - 1] = tmp;
			i--;
		}
	}
}
