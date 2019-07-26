/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:56 by smakni            #+#    #+#             */
/*   Updated: 2019/07/26 16:46:12 by sabri            ###   ########.fr       */
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

typedef	struct s_width
{
	int			perm;
	int			l;
	int			un;
	int			gn;
	int			s;
}				t_width;

typedef	struct	s_data
{
	char		link[4096];
	nlink_t		nb_link;
	char		*pw_name;
	char		*gr_name;
	off_t		st_size;
	time_t		time;
	char		*f_name;
	char		*mod;
	t_width		width;
	char		output[4096];
}				t_data;

typedef	struct s_path
{
	char		*path;
	time_t		time;
}				t_path;

typedef	struct	s_path_r
{
	t_path		path_lst[4096];
	int			nb_path;
}				t_path_r;

typedef	struct	s_env
{
	char 		*path;
	t_width		max_width;
	t_data		*data;
	int			ac;
	int			cursor;
	int			nb_files;
	int			nb_dir;
	int			capacity;
	char 		opt;
}				t_env;

void	option(char *av, char *opt);
int		realloc_tab(t_env *env);
void	swap_data(t_env *env);
void	swap_dir(t_path_r *path_r);
int		save_data(t_env *env, char *path, char *file_name, t_path_r *path_r);
int		save_output(t_env *env);
void	ft_qsort_data(t_data *data, int first, int last);
void	ft_qsort_dir(t_path_r *path_r, int first, int last);

#endif
