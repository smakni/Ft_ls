/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:02:19 by marvin            #+#    #+#             */
/*   Updated: 2019/09/10 20:41:31 by sabri            ###   ########.fr       */
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
		while (i - 1 >= 0 && e->data[i].time > e->data[i - 1].time)
		{
			tmp = e->data[i];
			e->data[i] = e->data[i - 1];
			e->data[i - 1] = tmp;
			i--;
		}
		while (i - 1 >= 0 && e->data[i].time == e->data[i - 1].time
		&& ft_strcmp(e->data[i].f_name, e->data[i - 1].f_name) < 0)
		{
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
}

void		swap_dir(t_env *e, t_path_r *path_r)
{
	int			i;
	t_path_r	tmp;

	i = 0;
	if (e->opt & T)
	{
		while (i - 1 >= 0 
		&& path_r->path_lst[i].time > path_r->path_lst[i - 1].time)
		{
			tmp = path_r[i];
			path_r[i] = path_r[i - 1];
			path_r[i - 1] = tmp;
			i--;
		}
		while (i - 1 >= 0 
		&& path_r->path_lst[i].time == path_r->path_lst[i - 1].time
		&& ft_strcmp(path_r->path_lst[i].path, path_r->path_lst[i - 1].path) < 0)
		{
			tmp = path_r[i];
			path_r[i] = path_r[i - 1];
			path_r[i - 1] = tmp;
			i--;
		}
	}
	else
	{	
		ft_printf("DEBUG[%s]\n", path_r->path_lst[i]);
		while (i - 1 >= 0
		&& ft_strcmp(path_r->path_lst[i].path, path_r->path_lst[i - 1].path) < 0)
		{
			tmp = path_r[i];
			path_r[i] = path_r[i - 1];
			path_r[i - 1] = tmp;
			i--;
		}
	}
}
