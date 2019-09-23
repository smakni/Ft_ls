/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:19 by smakni            #+#    #+#             */
/*   Updated: 2019/09/19 16:48:42 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	get_info(char *path, t_env *e)
{
	struct	stat	buf;
	t_path_r		path_r;

	path_r.nb_path = 0;
	if ((stat(path, &buf)) == -1)
	{
		ft_printf("ls: %s: No such file or directory\n", path);
		e->cursor++;
	}
	else
	{
		if ((buf.st_mode & S_IFMT) == S_IFDIR)
		{
			lst_dir(e, path, &path_r);
			print_data(e, path);
			e->cursor++;
			if (e->opt & R)
				lst_dir_r(e, &path_r, get_info);
		}
		else
		{
			extract_data(e, path, path, NULL);
			write_output(e);
			//ft_printf("%s\n", e->data[0].output);
			e->cursor++;
			e->nb_files = 0;
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
		arg_parsing(&e, &arg, ac, av);
	free(e.data);
    return (0);
}
