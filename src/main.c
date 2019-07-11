/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:19 by smakni            #+#    #+#             */
/*   Updated: 2019/07/11 18:36:55 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

// int getChmod(const char *path){
//     struct stat ret;

//     if (stat(path, &ret) == -1) {
//         return -1;
//     }

//     return (ret.st_mode & S_IRUSR)|(ret.st_mode & S_IWUSR)|(ret.st_mode & S_IXUSR)|/*owner*/
//         (ret.st_mode & S_IRGRP)|(ret.st_mode & S_IWGRP)|(ret.st_mode & S_IXGRP)|/*group*/
//         (ret.st_mode & S_IROTH)|(ret.st_mode & S_IWOTH)|(ret.st_mode & S_IXOTH);/*other*/
// }

void	print_stat(char *f_name, char *opt, char *path)
{
	struct stat 	buf;
	struct passwd 	*tmp_u;
	struct group	*tmp_g;
	char 			*time;

	if ((stat(path, &buf)) == -1)
	{
		ft_printf("print_stat : acces impossible a %s\n", path);
		return ;
	}
	if (*opt & L)
	{
		time = ctime((time_t *)&buf.st_mtimespec);
		tmp_u = getpwuid(buf.st_uid);
		tmp_g = getgrgid(tmp_u->pw_gid);
		ft_printf("[type-permissions] ");
		ft_printf("%4d ", buf.st_nlink);
		ft_printf("%s ", tmp_u->pw_name);
		ft_printf("%s ", tmp_g->gr_name);
		ft_printf("%7u ", buf.st_size);
		ft_printf("%.12s ", &time[4]);
	}
	ft_printf("%s\n", f_name);
}

void	lst_dir(char *f_name, void (*get_info)(char *, char *), char *opt)
{
	char			path[__DARWIN_MAXPATHLEN];
	struct dirent	*dir_ent;
	DIR				*dir;

	if ((dir = opendir(f_name)) == NULL)
	{
		ft_printf("lst_dir : impossibe d'ouvrir %s\n", f_name);
		return ;
	}
	while ((dir_ent = readdir(dir)) != NULL)
	{
		ft_sprintf(path, "%s/%s", f_name, dir_ent->d_name);
		// ft_printf("path = %s\n", path);
		if (dir_ent->d_name[0] == '.')
		{
			if (*opt & A)
			{
				print_stat(dir_ent->d_name, opt, path);
				if ((*opt & R)
				&& ft_strcmp(dir_ent->d_name, ".") != 0
				&& ft_strcmp(dir_ent->d_name, "..") != 0)
		 			(*get_info)(path, opt);
			}
			continue ;
		}
		if (*opt & R)
		 	(*get_info)(path, opt);
		print_stat(dir_ent->d_name, opt, path);
	}
	closedir(dir);
}

void	get_info(char *path, char *opt)
{
	struct	stat	buf;

	// ft_printf("\n>>>get_info<<<\n");
	if ((stat(path, &buf)) == -1)
	{
		ft_printf("get_info : acces impossible a %s\n", path);
		return ;
	}
	// ft_printf("mode = %d\n", buf.st_mode & S_IFMT);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_printf("\n>>>>enter[%s]\n\n", path);
		lst_dir(path, get_info, opt);
		ft_printf("\n>>>>>out\n\n");
	}
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
				option(av[i], &opt);
				if (i + 1 == ac && i + 1 < 3)
					get_info(".", &opt);
			}
			else
				get_info(av[i], &opt);
			i++;
		}
	}
    return (0);
}
