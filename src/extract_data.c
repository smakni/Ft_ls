/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:37:58 by smakni            #+#    #+#             */
/*   Updated: 2019/09/23 18:31:04 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static	int		check_width_link(nlink_t nb_link)
{
	int i;

	i = 0;
	while (nb_link > 0)
	{
		nb_link /= 10;
		i++;
	}
	if (i == 0)
		return (1);
	return (i);
}

static	int		check_width_st_size(off_t st_size)
{
	int i;

	i = 0;
	while (st_size > 0)
	{
		st_size /= 10;
		i++;
	}
	if (i == 0)
		return (1);
	return (i);
}

int				check_stat(t_env *e, char *path, struct stat *buf)
{
	if (readlink(path, e->data[e->nb_files].link, sizeof(e->data[e->nb_files].link)) == -1)
	{
		if ((stat(path, buf)) == -1)
		{
			ft_printf(IMPOSSIBLE_ACCES, path);
			return (-1);
		}
	}
	else if ((lstat(path, buf)) == -1)
	{
			ft_printf(IMPOSSIBLE_ACCES, path);
			return(-1);
	}
	return (0);
}

void	save_data(t_env *e, struct passwd *uid,
						struct group *gid, struct stat *buf)
{
	if (e->opt & L)
	{
		e->data[e->nb_files].nb_link = buf->st_nlink;
		if ((e->data[e->nb_files].width.l = check_width_link(e->data[e->nb_files].nb_link)) > e->max_width.l)
			e->max_width.l = e->data[e->nb_files].width.l;
		e->data[e->nb_files].pw_name = uid->pw_name;
		if ((e->data[e->nb_files].width.un = ft_strlen(e->data[e->nb_files].pw_name)) > e->max_width.un)
			e->max_width.un = e->data[e->nb_files].width.un;
		e->data[e->nb_files].gr_name = gid->gr_name;
		if ((e->data[e->nb_files].width.gn = ft_strlen(e->data[e->nb_files].gr_name)) > e->max_width.gn)
			e->max_width.gn = e->data[e->nb_files].width.gn;
		e->data[e->nb_files].st_size = buf->st_size;
		if ((e->data[e->nb_files].width.s = check_width_st_size(e->data[e->nb_files].st_size)) > e->max_width.s)
			e->max_width.s = e->data[e->nb_files].width.s;
	}
}

void			save_recurcive_dir(t_env *e, struct stat *buf, char *path, t_path_r *path_r)
{
	if ((e->opt & R) && (buf->st_mode & S_IFMT) == S_IFDIR
			&& ft_strcmp(e->data[e->nb_files].f_name, "..") != 0
			&& ft_strcmp(e->data[e->nb_files].f_name, ".") != 0)
	{
		path_r->path_lst[path_r->nb_path].path = ft_strdup(path);
		path_r->path_lst[path_r->nb_path].time = buf->st_mtime;
		swap_dir(e, path_r);
		path_r->nb_path++;
	}
}

void			extract_data(t_env *e, char *path, char *file_name, t_path_r *path_r)
{
	struct stat		buf;
	struct passwd	*uid;
	struct group	*gid;

	if (e->nb_files >= e->capacity)
		if (realloc_tab(e) == -1)
			exit(-1);
	if (check_stat(e, path, &buf) == -1)
		return ;
	ft_sprintf(e->data[e->nb_files].f_name, "%s", file_name);
	e->data[e->nb_files].time = buf.st_mtime;
	if (!(uid = getpwuid(buf.st_uid)))
		return ;
	if (!(gid = getgrgid(uid->pw_gid)))
		return ;
	if (e->opt & L)
		e->max_width.perm = write_mod(e, &buf, path);
	save_data(e, uid, gid, &buf);
	swap_data(e);
	save_recurcive_dir(e, &buf, path, path_r);
	e->total += buf.st_blocks;
	e->nb_files++;
}
