/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:19 by smakni            #+#    #+#             */
/*   Updated: 2019/07/08 18:40:09 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		get_dir_info(t_env *env, char *dir_path)
{
    env->dir[env->nb_dir] = opendir(dir_path);
	if (env->dir[env->nb_dir] == NULL)
		return (ERROR);
	return (0);
}

int		lst_repo(t_env *env, int index)
{
	struct dirent	*dp;

	while ((dp = readdir(env->dir[index])) != 0)
    {	
		if (dp->d_name[0] != '.')
		{
			ft_printf("name : %s | type : %d | nb_reclen = %u\n", dp->d_name, dp->d_type, dp->d_reclen);
		}
		if (dp->d_type == DT_DIR)
		{
			env->nb_dir++;
			get_dir_info(env, dp->d_name);
		}
    }
	closedir(env->dir[index]);
	return (0);
}

int		main(int ac, char **av)
{
	t_env env;
	// int i = 0;

	if (ac > 1)
	{
		ft_bzero(&env, sizeof(t_env));
		get_dir_info(&env, av[1]);
		lst_repo(&env, 0);
		ft_printf("nb_dir_in : %d\n", env.nb_dir);
		// while (i < env.nb_dir)
		  	// ft_printf("saved_dir = %s\n", env->dir[i])
	}
    return (0);
}
