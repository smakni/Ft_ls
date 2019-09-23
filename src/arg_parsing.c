/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:26:30 by smakni            #+#    #+#             */
/*   Updated: 2019/09/19 18:02:24 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void			extract_arg(t_env *e, char *path, char *file_name, t_path_r *path_r)
{
	struct stat		buf;
	struct passwd	*uid;
	struct group	*gid;

	if (e->nb_files >= e->capacity)
		if (realloc_tab(e) == -1)
			exit(-1);
	if (readlink(path, e->data[e->nb_files].link, sizeof(e->data[e->nb_files].link)) == -1)
	{
		if ((stat(path, &buf)) == -1)
		{
			ft_printf("save_stat : acces impossible a %s\n", path);
			return ;
		}
	}
	else if ((lstat(path, &buf)) == -1)
	{
			ft_printf("save_stat : acces impossible a %s\n", path);
			return ;
	}
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
	{
		path_r->path_lst[path_r->nb_path].path = ft_strdup(path);
		path_r->path_lst[path_r->nb_path].time = buf.st_mtime;
		swap_dir(e, path_r);
		path_r->nb_path++;
		return ;
	}
	ft_sprintf(e->data[e->nb_files].f_name, "%s", file_name);
	e->data[e->nb_files].time = buf.st_mtime;
	if (!(uid = getpwuid(buf.st_uid)))
		return ;
	if (!(gid = getgrgid(uid->pw_gid)))
		return ;
	if (e->opt & L)
		e->max_width.perm = write_mod(e, &buf, path);
	save_data(e, uid, gid, &buf);
	swap_data(e);
	e->nb_files++;
}

void	check_arg(t_env *e, t_path_r *arg, int ac, char **av)
{
	int i;
	
	i = 1;
	while(i < ac)
	{
		if (av[i][0] == '-' && av[i][1] != 0)
			option(av[i], &e->opt);
		else
		{
			extract_arg(e, av[i], av[i], arg);
			write_output(e);
		}
		i++;
	}
	e->nb_arg = arg->nb_path;
}

void	arg_parsing(t_env *e, t_path_r *arg, int ac, char **av)
{
	int i;
	
	check_arg(e, arg, ac, av);
	if (e->opt > 0 && arg->nb_path == 0 && ac == 2)
		get_info(".", e);
	else
	{
		print_data(e, NULL);
		if (e->nb_files > 0)
			e->cursor++;
		i = 0;
		while(i < arg->nb_path)
		{
			get_info(arg->path_lst[i].path, e);
			free(arg->path_lst[i++].path);
		}
	}
}

