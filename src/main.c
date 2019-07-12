/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:19 by smakni            #+#    #+#             */
/*   Updated: 2019/07/12 16:16:52 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

// int getChmod(const char *path){
//     struct stat ret;
//{
//     if (stat(path, &ret) == -1) {
//         return -1;
//  	}
//     return (ret.st_mode & S_IRUSR)|(ret.st_mode & S_IWUSR)|(ret.st_mode & S_IXUSR)|/*owner*/
//         (ret.st_mode & S_IRGRP)|(ret.st_mode & S_IWGRP)|(ret.st_mode & S_IXGRP)|/*group*/
//         (ret.st_mode & S_IROTH)|(ret.st_mode & S_IWOTH)|(ret.st_mode & S_IXOTH);/*other*/
// }

// stocker directement avec le bon index(orde definis par si option -t ou pas)

// int		crs(char)
// {
// 	if (env->data[])
// }

void	print_data(t_env *env)
{
	int i;

	i = 0;
	//ft_printf("nb = %d\n", env->nb_files);
	while (i < env->nb_files) 
	{
		// ft_printf("time = %ld\n", env->data[i]->time);
		ft_printf("%s", env->data[i++].output);
	}
	//free(env->data);
	env->nb_files = 0;
}

void	save_data(t_env *env, char *path, char *file_name)
{
	struct stat 	buf;
	struct passwd 	*uid;
	struct group	*gid;
	char 			*time;
	int				ret;

	ret = 0;
	if (env->nb_files >= env->capacity)
	{
		if (ft_realloc_tab(env) == -1)
		{
			exit (-1);
		}
	}
	if ((stat(path, &buf)) == -1)
	{
		ft_printf("print_stat : acces impossible a %s\n", path);
		return ;
	}
	if (env->opt & L)
	{
		env->data[env->nb_files].time = buf.st_mtime;
		time = ctime((time_t *)&buf.st_mtime);
		uid = getpwuid(buf.st_uid);
		gid = getgrgid(uid->pw_gid);
		ret = ft_sprintf(&env->data[env->nb_files].output[ret], "[type-permissions] ");
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%2d ", buf.st_nlink);
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%s ", uid->pw_name);
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%s ", gid->gr_name);
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%6u ", buf.st_size);
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%.12s ", &time[4]);
	}
	ft_sprintf(&env->data[env->nb_files].output[ret], "%s\n", file_name);
	env->nb_files++;
	// print_data(env);
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

	}if (env->data != NULL)
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
		ft_printf("\n>>>>enter[%s]\n\n", path);
		lst_dir(env, path, get_info);
		print_data(env);
		ft_printf("\n>>>>>out\n\n");
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
