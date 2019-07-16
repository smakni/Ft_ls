/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:19 by smakni            #+#    #+#             */
/*   Updated: 2019/07/16 15:48:59 by smakni           ###   ########.fr       */
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
		{
			// ft_printf("time = %ld\n", env->data[i]->time);
			ft_printf("%s", env->data[i--].output);
		}
	}
	else
	{
		while (i < env->nb_files)
		{
			// ft_printf("time = %ld\n", env->data[i]->time);
			ft_printf("%s", env->data[i++].output);
		}
	}
	env->nb_files = 0;
}

void	lst_dir(t_env *env, char *dir_name, void (*get_info)(char *, t_env *))
{
	char			path[1024];
	struct dirent	*dir_ent;
	DIR				*dir;

	if ((dir = opendir(dir_name)) == NULL)
	{
		ft_printf("lst_dir : impossibe d'ouvrir %s\n", path);
		return ;
	}
	while ((dir_ent = readdir(dir)) != NULL)
	{
		ft_sprintf(path, "%s/%s", dir_name, dir_ent->d_name);
		if (dir_ent->d_name[0] == '.')
		{
			if (env->opt & A)
			{
				save_data(env, path, dir_ent->d_name);
				if ((env->opt & R)
				&& ft_strcmp(dir_ent->d_name, ".") != 0
				&& ft_strcmp(dir_ent->d_name, "..") != 0)
		 		 	(*get_info)(path, env);
			}
			continue ;
		}
		save_data(env, path, dir_ent->d_name);
		if (env->opt & R)
		{
			print_data(env);
			(*get_info)(path, env);
		}

	}
	print_data(env);
	closedir(dir);
}

void	get_info(char *path,t_env *env)
{
	struct	stat	buf;

	// ft_printf("nb_files = %d\n", env->nb_files);
	if ((stat(path, &buf)) == -1)
	{
		ft_printf("get_info : acces impossible a %s\n", path);
	}
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_printf(">%s\n", path);
		lst_dir(env, path, get_info);
		//print_data(env);
		ft_printf(">|\n");
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
