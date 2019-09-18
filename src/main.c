/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:19 by smakni            #+#    #+#             */
/*   Updated: 2019/09/10 20:26:50 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	get_info(char *path,t_env *e)
{
	struct	stat	buf;
	t_path_r		path_r;

	path_r.nb_path = 0;
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
			extract_data(e, path, path, NULL);
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
				arg->path_lst[arg->nb_path].time = buf.st_mtime;
				swap_dir(e, arg);
				arg->nb_path++;
			}
		}
		i++;
	}
	if (e->opt > 0 && arg->nb_path == 0)
		get_info(".", e);
	else
	{
		i = 0;
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
