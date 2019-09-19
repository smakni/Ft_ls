/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:26:30 by smakni            #+#    #+#             */
/*   Updated: 2019/09/19 15:02:33 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	check_arg(t_env *e, t_path_r *arg, int ac, char **av)
{
	int i;
	struct stat buf;
	
	i = 1;
	while(i < ac)
	{
		if (av[i][0] == '-' && av[i][1] != 0)
			option(av[i], &e->opt);
		else
		{
			arg->path_lst[arg->nb_path].path = ft_strdup(av[i]);
			arg->path_lst[arg->nb_path].time = buf.st_mtime;
			swap_dir(e, arg);
			arg->nb_path++;
		}
		i++;
	}
	e->nb_arg = arg->nb_path;
}

void	arg_parsing(t_env *e, t_path_r *arg, int ac, char **av)
{
	int i;
	
	check_arg(e, arg, ac, av);
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

