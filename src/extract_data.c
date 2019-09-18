/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:37:58 by smakni            #+#    #+#             */
/*   Updated: 2019/09/10 20:26:27 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int	check_width_link(nlink_t nb_link)
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

static int	check_width_st_size(off_t st_size)
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

static void	write_type(t_env *e, struct stat *buf)
{
	ft_memset(e->data[e->nb_files].output, ' ', 4092);
	ft_memset(e->data[e->nb_files].output, '-', 10);
	if ((buf->st_mode & S_IFMT) == S_IFDIR)
		e->data[e->nb_files].output[0] = 'd';
	else if ((buf->st_mode & S_IFMT) == S_IFLNK)
		e->data[e->nb_files].output[0] = 'l';
}

static	int		write_mod(t_env *e, struct stat *buf, char *path)
{
	char namebuf[MAX_FSIZE];

	//(void)path;
	write_type(e, buf);
	if (buf->st_mode & S_IRUSR)
		e->data[e->nb_files].output[1] = 'r';
	if (buf->st_mode & S_IWUSR)
		e->data[e->nb_files].output[2] = 'w';
	if (buf->st_mode & S_IXUSR)
		e->data[e->nb_files].output[3] = 'x';
	if (buf->st_mode & S_IRGRP)
		e->data[e->nb_files].output[4] = 'r';
	if (buf->st_mode & S_IWGRP)
		e->data[e->nb_files].output[5] = 'w';
	if (buf->st_mode & S_IXGRP)
		e->data[e->nb_files].output[6] = 'x';
	if (buf->st_mode & S_IROTH)
		e->data[e->nb_files].output[7] = 'r';
	if (buf->st_mode & S_IWOTH)
		e->data[e->nb_files].output[8] = 'w';
	if (buf->st_mode & S_IXOTH)
		e->data[e->nb_files].output[9] = 'x';
	if (listxattr(path, namebuf, MAX_FSIZE, XATTR_NOFOLLOW) > 0)
		e->data[e->nb_files].output[10] = '@';
	return (10);
}

static	void	save_data(t_env *e, struct passwd *uid,
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

int			extract_data(t_env *e, char *path, char *file_name, t_path_r *path_r)
{
	struct stat		buf;
	struct passwd	*uid;
	struct group	*gid;

	if (e->nb_files >= e->capacity)
		if (realloc_tab(e) == -1)
			exit(-1);
	if (readlink(path, e->data[e->nb_files].link, sizeof(e->data[e->nb_files].link)) == -1)
	{
		if ((stat(path, &buf)) == -1)
		{
			ft_printf("save_stat : acces impossible a %s\n", path);
			return (0);
		}
	}
	else if ((lstat(path, &buf)) == -1)
	{
			ft_printf("save_stat : acces impossible a %s\n", path);
			return (0);
	}
	if ((e->opt & R) && (buf.st_mode & S_IFMT) == S_IFDIR
			&& ft_strcmp(file_name, "..") != 0
			&& ft_strcmp(file_name, ".") != 0)
	{
		path_r->path_lst[path_r->nb_path].path = ft_strdup(path);
		path_r->path_lst[path_r->nb_path].time = buf.st_mtime;
		swap_dir(e, path_r);
		path_r->nb_path++;
	}
	ft_sprintf(e->data[e->nb_files].f_name, "%s", file_name);
	e->data[e->nb_files].time = buf.st_mtime;
	if (!(uid = getpwuid(buf.st_uid)))
		return (0);
	if (!(gid = getgrgid(uid->pw_gid)))
		return (0);
	if (e->opt & L)
		e->max_width.perm = write_mod(e, &buf, path);
	save_data(e, uid, gid, &buf);
	swap_data(e);
	e->nb_files++;
	return (buf.st_blocks);
}
