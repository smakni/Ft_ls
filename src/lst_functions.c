/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:04:54 by sabri             #+#    #+#             */
/*   Updated: 2019/09/23 00:02:19 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	lst_dir_r(t_env *e, t_path_r *path_r, void (*get_info)(char *, t_env *))
{
	int i;

	i = 0;
	if (e->opt & SR)
	{
		i = path_r->nb_path - 1;
		while (i >= 0)
		{
			(*get_info)(path_r->path_lst[i].path, e);
			free(path_r->path_lst[i].path);
			i--;
		}
	}
	else
	{
		while (i < path_r->nb_path)
		{
			(*get_info)(path_r->path_lst[i].path, e);
			free(path_r->path_lst[i].path);
			i++;
		}
	}
}

void	lst_dir(t_env *e, char *dir_name, t_path_r *path_r)
{
	char			path[1024];
	struct dirent	*dir_ent;
	DIR				*dir;


	e->total = 0;
	e->nb_files = 0;
	ft_bzero(path, sizeof(path));
	if ((dir = opendir(dir_name)) == NULL)
	{
		ft_printf(NO_PERM, dir_name);
		return ;
	}
	while ((dir_ent = readdir(dir)) != NULL)
	{
		if (ft_strcmp("/", dir_name) != 0)
			ft_sprintf(path, "%s/%s", dir_name, dir_ent->d_name);
		else
			ft_sprintf(path, "%s%s", dir_name, dir_ent->d_name);
		if (dir_ent->d_name[0] == '.')
		{
			if (e->opt & A)
				extract_data(e, path, dir_ent->d_name, path_r);
			continue ;
		}
		extract_data(e, path, dir_ent->d_name, path_r);
	}
	write_output(e);
	closedir(dir);
}
