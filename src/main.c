/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:19 by smakni            #+#    #+#             */
/*   Updated: 2019/07/26 18:00:04 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	print_data(t_env *env)
{
	int i;

	i = 0;
	alphaqsort_data(env->data, 0, env->nb_files - 1);
	if (env->opt & T)
		ft_qsort_data(env->data, 0, env->nb_files - 1);
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

void	lst_dir_r(t_env *env, t_path_r *path_r, void (*get_info)(char *, t_env *))
{
	int i;

	i = 0;
	alphaqsort_dir(path_r, 0, path_r->nb_path - 1);
	if (env->opt & T)
		ft_qsort_dir(path_r, 0, path_r->nb_path - 1);
	if (env->opt & SR)
	{
		i = path_r->nb_path - 1;
		while (i >= 0)
		{
			(*get_info)(path_r->path_lst[i].path, env);
			free(path_r->path_lst[i].path);
			i--;
		}
	}
	else
	{
		while (i < path_r->nb_path)
		{
			(*get_info)(path_r->path_lst[i].path, env);
			free(path_r->path_lst[i].path);
			i++;
		}
	}
}

void	lst_dir(t_env *env, char *dir_name, t_path_r *path_r)
{
	char			path[1024];
	struct dirent	*dir_ent;
	DIR				*dir;
	int				total;


	total = 0;
	env->nb_files = 0;
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
			if (env->opt & A)
				total += save_data(env, path, dir_ent->d_name, path_r);
			continue ;
		}
		total += save_data(env, path, dir_ent->d_name, path_r);
	}
	if (env->opt & L && env->nb_files > 0)
		ft_printf("total %d\n", total);
	save_output(env);
	closedir(dir);
	return ;
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

void	get_info(char *path,t_env *env)
{
	struct	stat	buf;
	t_path_r		path_r;

	ft_bzero(&path_r, sizeof(path_r));
	if ((stat(path, &buf)) == -1)
		ft_printf("ft_ls: %s: No such file or directory\n", path);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
	{
		print_path(env, path);
		lst_dir(env, path, &path_r);
		print_data(env);
		env->cursor++;
		if (env->opt & R)
			lst_dir_r(env, &path_r, get_info);
	}
	else
	{
		save_data(env, path, path, NULL);
		save_output(env);
		print_data(env);
		env->cursor++;
		env->nb_files = 0;
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
