/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:56 by smakni            #+#    #+#             */
/*   Updated: 2019/07/18 17:45:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <libft.h>
# include <ft_printf.h>
# include <get_next_line.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>


# define R 	1
# define L 	2
# define A 	4
# define SR 8
# define T 	16

# define CAPACITY 1024

typedef	struct	s_data
{
	time_t		time;
	char		*f_name;
	char		*mod;
	char		output[4096];
}				t_data;

typedef	struct s_path
{
	char		*path;
	time_t		time;
}				t_path;

typedef	struct	s_path_r
{
	t_path		path_lst[CAPACITY];
	int			nb_path;
}				t_path_r;

typedef	struct	s_env
{
	t_data		*data;
	int			nb_files;
	int			capacity;
	char 		opt;
}				t_env;

void	option(char *av, char *opt);
int		realloc_tab(t_env *env);
void	swap_data(t_env *env);
void	swap_dir(t_path_r *path_r);
void	save_data(t_env *env, char *path, char *file_name, t_path_r *path_r);

#endif
