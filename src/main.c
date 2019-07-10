/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:19 by smakni            #+#    #+#             */
/*   Updated: 2019/07/10 18:59:02 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	print_stat(char *name, char *opt, char *path)
{
	struct stat tmp;
	
	if ((stat(path, &tmp)) == -1)
	{
		ft_printf("print_stat : acces impossible a %s\n", name);
		return ;
	}
	if (*opt & L)
	{
		ft_printf("permissions ");
		ft_printf("%d ", tmp.st_mode);
		ft_printf("Ownder_name ");
		ft_printf("group_name ");
		ft_printf("%6u ", tmp.st_size);
		//ft_printf("%s ", asctime(gmtime(&f_stat->st_mtimespec)));
	}
	ft_printf("%s\n", name);
}

void	lst_dir(char *f_name, void (*get_info)(char *, char *), char *opt)
{
	char			path[MAX_PATH];
	struct dirent	*dir_ent;
	DIR				*dir;

	if ((dir = opendir(f_name)) == NULL)
	{
		ft_printf("balayer_rep : impossibe d'ouvrir %s\n", f_name);
		return ;
	}
	while ((dir_ent = readdir(dir)) != NULL)
	{
		if (dir_ent->d_name[0] == '.')
		{
			if (*opt & A)
			{
				print_stat(dir_ent->d_name, opt, path);
				if ((*opt & R)
				&& ft_strcmp(dir_ent->d_name, ".") != 0
				&& ft_strcmp(dir_ent->d_name, "..") != 0)
				{
					ft_sprintf(path, "%s/%s", f_name, dir_ent->d_name);
		 			(*get_info)(path, opt);
				}
			}
			continue ;
		}
		else if (*opt & R)
		{
			ft_sprintf(path, "%s/%s", f_name, dir_ent->d_name);
		 	(*get_info)(path, opt);
		}
		print_stat(dir_ent->d_name, opt, path);
	}
	closedir(dir);
}

void	get_info(char *f_name, char *opt)
{
	struct	stat	f_stat;

	if ((stat(f_name, &f_stat)) == -1)
	{
		ft_printf("get_info : acces impossible a %s\n", f_name);
		return ;
	}
	if ((f_stat.st_mode & S_IFMT) == S_IFDIR)
		lst_dir(f_name, get_info, opt);
}

void	fill_opt(char *av, char *opt)
{
	if (ft_strchr(av, 'R') != 0)
		*opt |= 1;
	if (ft_strchr(av, 'l') != 0)
		*opt |= 2;
	if (ft_strchr(av, 'a') != 0)
		*opt |= 4;
}

int		main(int ac, char **av)
{
	char opt;
	int i;

	opt = 0;
	i = 1;
	if (ac == 1)
	 	get_info(".", &opt);
	else
	{
		while(i < ac)
		{
			if (av[i][0] == '-')
			{
				fill_opt(av[i], &opt);
				if (i + 1 == ac)
					get_info(".", &opt);
			}
			else
				get_info(av[i], &opt);
			i++;
		}
	}
    return (0);
}
