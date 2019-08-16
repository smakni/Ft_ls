/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:19 by smakni            #+#    #+#             */
/*   Updated: 2019/08/16 22:27:18 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	lst_dir_r(t_env *e, t_path_r *path_r, void (*get_info)(char *, t_env *))
{
	int i;

	i = 0;
	alphaqsort_dir(path_r, 0, path_r->nb_path - 1);
	if (e->opt & T)
		qsort_dir(path_r, 0, path_r->nb_path - 1);
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
	int				total;


	total = 0;
	e->nb_files = 0;
	ft_bzero(path, sizeof(path));
	if ((dir = opendir(dir_name)) == NULL)
	{
		ft_printf("ft_ls: cannot open directory '%s': Permission denied\n", dir_name);
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
				total += save_data(e, path, dir_ent->d_name, path_r);
			continue ;
		}
		total += save_data(e, path, dir_ent->d_name, path_r);
	}
	if (e->opt & L && e->nb_files > 0)
		ft_printf("total %d\n", total);
	save_output(e);
	closedir(dir);
	return ;
}

void	get_info(char *path,t_env *e) // check if link don't lst
{
	struct	stat	buf;
	t_path_r		path_r;

	ft_bzero(&path_r, sizeof(path_r));
	if ((stat(path, &buf)) == -1)
		ft_printf("ft_ls: %s: No such file or directory\n", path);
	else
	{
		if ((buf.st_mode & S_IFMT) == S_IFDIR)
		{
			print_path(e, path);
			lst_dir(e, path, &path_r);
			print_data(e);
			e->cursor++;
			if (e->opt & R)
				lst_dir_r(e, &path_r, get_info);
		}
		else
		{
			save_data(e, path, path, NULL);
			save_output(e);
			print_data(e);
			e->cursor++;
			e->nb_files = 0;
		}
	}
}

void	check_arg(t_env *e, t_path_r *arg, int ac, char **av)
{
	int i;
	struct stat buf;
	
	i = 1;
	while(i < ac)
	{
		if (av[i][0] == '-')
			option(av[i], &e->opt);
		else
		{
			if ((stat(av[i], &buf)) == -1)
				ft_printf("save_stat : acces impossible a %s\n", av[i]);
			else
			{
				arg->path_lst[arg->nb_path].path = ft_strdup(av[i]);
				arg->path_lst[arg->nb_path++].time = buf.st_mtime;
			}
		}
		i++;
	}
	if (e->opt > 0 && arg->nb_path == 0)
		get_info(".", e);
	else
	{
		i = 0;
		// alphaqsort_dir(arg, 0, arg->nb_path - 1);
		// if (e->opt & T)
		// 	qsort_dir(arg, 0, arg->nb_path - 1);
		while(i < arg->nb_path)
		{
			get_info(arg->path_lst[i].path, e);
			free(arg->path_lst[i++].path);
		}
	}
}

int		main(int ac, char **av)
{
	t_env		e;
	t_path_r	arg;

	ft_bzero(&e, sizeof(t_env));
	ft_bzero(&arg, sizeof(t_path_r));
	e.capacity = CAPACITY;
	if ((e.data = ft_memalloc(sizeof(t_data) * CAPACITY)) == NULL)
		return (-1);
	if (ac == 1)
	 	get_info(".", &e);
	else
		check_arg(&e, &arg, ac, av);
	free(e.data);
    return (0);
}
