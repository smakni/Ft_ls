/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:19 by smakni            #+#    #+#             */
/*   Updated: 2019/07/18 18:52:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	print_data(t_env *env)
{
	int i;

	i = 0;
	if (env->opt & T)
		swap_data(env);
	if (env->opt & SR)
	{
		i = env->nb_files - 1;
		while (i >= 0)
			ft_printf("%s", env->data[i--].output);
	}
	else
	{
		while (i < env->nb_files)
			ft_printf("%s", env->data[i++].output);
	}
	env->nb_files = 0;
}

void	lst_dir_r(t_env *env, t_path_r *path_r, void (*get_info)(char *, t_env *))
{
	int i;

	i = 0;
	while (i < path_r->nb_path)
	{
		ft_printf("path_list = %s\n", path_r->path_lst[i++]);
	}
	i = 0;
	if (env->opt & T)
		swap_dir(path_r);
	if (env->opt & SR)
	{
		i = path_r->nb_path - 1;
		while (i >= 0)
			(*get_info)(path_r->path_lst[i--].path, env);
	}
	else
	{
		while (i < path_r->nb_path)
			(*get_info)(path_r->path_lst[i++].path, env);
	}
}

t_path_r lst_dir(t_env *env, char *dir_name)
{
	char			path[1024];
	struct dirent	*dir_ent;
	DIR				*dir;
	t_path_r		path_r;


	ft_bzero(&path_r, sizeof(path_r));
	if ((dir = opendir(dir_name)) == NULL)
	{
		ft_printf("lst_dir : impossibe d'ouvrir %s\n", dir_name);
		return (path_r);
	}
	while ((dir_ent = readdir(dir)) != NULL)
	{
		ft_sprintf(path, "%s/%s", dir_name, dir_ent->d_name);
		if (dir_ent->d_name[0] == '.')
		{
			if (env->opt & A)
				save_data(env, path, dir_ent->d_name, &path_r);
			continue ;
		}
		save_data(env, path, dir_ent->d_name, &path_r);
	}
	closedir(dir);
	return (path_r);
}

void	get_info(char *path,t_env *env)
{
	struct	stat	buf;
	t_path_r		path_r;

	if ((stat(path, &buf)) == -1)
		ft_printf("get_info : acces impossible a %s\n", path);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_printf("%s:\n", path);
		path_r = lst_dir(env, path);
		print_data(env);
		ft_printf("\n");
		if (env->opt & R)
			lst_dir_r(env, &path_r, get_info);
	}
}

int		main(int ac, char **av)
{
	t_env env;
	int i;

	i = 1;
	ft_bzero(&env, sizeof(env));
	env.capacity = CAPACITY;
	if((env.data = ft_memalloc(sizeof(t_data) * CAPACITY)) == NULL)
		return (-1);
	if (ac == 1)
	 	get_info(".", &env);
	else
	{
		while(i < ac)
		{
			if (av[i][0] == '-')
			{
				option(av[i], &env.opt);
				if (i + 1 == ac && i + 1 < 3)
					get_info(".", &env);
			}
			else
				get_info(av[i], &env);
			i++;
		}
	}
	free(env.data);
    return (0);
}
