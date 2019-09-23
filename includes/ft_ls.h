/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:56 by smakni            #+#    #+#             */
/*   Updated: 2019/09/23 10:05:17 by smakni           ###   ########.fr       */
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
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

# if __APPLE__
#    define MAX_FSIZE    1024
#    define st_mtime    st_mtimespec.tv_sec
#	 define	SPE			2
# elif __linux__
#    define MAX_FSIZE    256
#    define S_ISVTX    __S_ISVTX
#    define S_ISWHT(x)    0
#	 define	SPE			1
# endif

# define R 	1
# define L 	2
# define A 	4
# define SR 8
# define T 	16

# define CAPACITY 	1024
# define NO_PERM	"ls: cannot open directory '%s': Permission denied\n"

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
	char		link[MAX_FSIZE];
	nlink_t		nb_link;
	char		*pw_name;
	char		*gr_name;
	off_t		st_size;
	time_t		time;
	char		f_name[MAX_FSIZE];
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
	int			total;
	int			cursor;
	int			nb_files;
	int			capacity;
	int			nb_arg;
	char 		opt;
}				t_env;

void	option(char *av, char *opt);
int		realloc_tab(t_env *e);
void	swap_data(t_env *e);
void	swap_dir(t_env *e, t_path_r *path_r);
void	extract_data(t_env *e, char *path, char *file_name, t_path_r *path_r);
void	write_output(t_env *e);
int		write_mod(t_env *e, struct stat *buf, char *path);
void	qsort_data(t_data *data, int first, int last);
void	qsort_dir(t_path_r *path_r, int first, int last);
void	alphaqsort_data(t_data *data, int first, int last);
void	alphaqsort_dir(t_path_r *path_r, int first, int last);
void	print_data(t_env *e, char *path);
void	lst_dir_r(t_env *e, t_path_r *path_r, void (*get_info)(char *, t_env *));
void	lst_dir(t_env *e, char *dir_name, t_path_r *path_r);
void	arg_parsing(t_env *e, t_path_r *arg, int ac, char **av);
void	get_info(char *path, t_env *e);
void	save_data(t_env *e, struct passwd *uid,
						struct group *gid, struct stat *buf);

#endif
