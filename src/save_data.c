/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:37:58 by smakni            #+#    #+#             */
/*   Updated: 2019/07/24 23:11:17 by sabri            ###   ########.fr       */
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

static void	check_type(t_env *env, struct stat *buf)
{
	ft_memset(env->data[env->nb_files].output, ' ', 4092);
	ft_memset(env->data[env->nb_files].output, '-', 10);
	if ((buf->st_mode & S_IFMT) == S_IFDIR)
		env->data[env->nb_files].output[0] = 'd';
	else if ((buf->st_mode & S_IFMT) == S_IFLNK)
		env->data[env->nb_files].output[0] = 'l';
}

static	int		save_mod(t_env *env, struct stat *buf)
{
	if (buf->st_mode & S_IRUSR)
		env->data[env->nb_files].output[1] = 'r';
	if (buf->st_mode & S_IWUSR)
		env->data[env->nb_files].output[2] = 'w';
	if (buf->st_mode & S_IXUSR)
		env->data[env->nb_files].output[3] = 'x';
	if (buf->st_mode & S_IRGRP)
		env->data[env->nb_files].output[4] = 'r';
	if (buf->st_mode & S_IWGRP)
		env->data[env->nb_files].output[5] = 'w';
	if (buf->st_mode & S_IXGRP)
		env->data[env->nb_files].output[6] = 'x';
	if (buf->st_mode & S_IROTH)
		env->data[env->nb_files].output[7] = 'r';
	if (buf->st_mode & S_IWOTH)
		env->data[env->nb_files].output[8] = 'w';
	if (buf->st_mode & S_IXOTH)
		env->data[env->nb_files].output[9] = 'x';
	return (10);
}

static	void	save_info(t_env *env, struct passwd *uid,
						struct group *gid, struct stat *buf)
{
	if (env->opt & L) //remplacer les width avec les max ans t_width
	{
		env->data[env->nb_files].nb_link = buf->st_nlink;
		if ((env->data[env->nb_files].width.l = check_width_link(env->data[env->nb_files].nb_link)) > env->max_width.l)
			env->max_width.l = env->data[env->nb_files].width.l;
		env->data[env->nb_files].pw_name = uid->pw_name;
		if ((env->data[env->nb_files].width.un = ft_strlen(env->data[env->nb_files].pw_name)) > env->max_width.un)
			env->max_width.un = env->data[env->nb_files].width.un;
		env->data[env->nb_files].gr_name = gid->gr_name;
		if ((env->data[env->nb_files].width.gn = ft_strlen(env->data[env->nb_files].gr_name)) > env->max_width.gn)
			env->max_width.gn = env->data[env->nb_files].width.gn;
		env->data[env->nb_files].st_size = buf->st_size;
		if ((env->data[env->nb_files].width.s = check_width_st_size(env->data[env->nb_files].st_size)) > env->max_width.s)
			env->max_width.s = env->data[env->nb_files].width.s;
	}
}

int			save_data(t_env *env, char *path, char *file_name, t_path_r *path_r)
{
	struct stat		buf;
	struct passwd	*uid;
	struct group	*gid;
	char			link[1024];

	ft_bzero(&link, sizeof(link));
	if (env->nb_files >= env->capacity)
		if (realloc_tab(env) == -1)
			exit(-1);
	if (readlink(path, env->data[env->nb_files].link, sizeof(link)) == -1)
	{
		if ((stat(path, &buf)) == -1)
		{
			ft_printf("save_stat : acces impossible a %s\n", path);
			return (0);
		}
	}
	else
	{
		if ((lstat(path, &buf)) == -1)
		{
			ft_printf("save_stat : acces impossible a %s\n", path);
			return (0);
		}
	}
	check_type(env, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR && ft_strcmp(file_name, "..") != 0
			&& ft_strcmp(file_name, ".") != 0)
	{
		path_r->path_lst[path_r->nb_path].path = ft_strdup(path);
		path_r->path_lst[path_r->nb_path++].time = buf.st_mtime;
	}
	env->data[env->nb_files].f_name = file_name;
	env->data[env->nb_files].time = buf.st_mtime;
	if (!(uid = getpwuid(buf.st_uid)))
		return (0);
	if (!(gid = getgrgid(uid->pw_gid)))
		return (0);
	if (env->opt & L)
		env->max_width.perm = save_mod(env, &buf);
	save_info(env, uid, gid, &buf);
	env->nb_files++;
	return (buf.st_blocks);
}
