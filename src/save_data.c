/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:37:58 by smakni            #+#    #+#             */
/*   Updated: 2019/07/19 15:34:13 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	check_type(t_env *env, struct stat *buf)
{
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

static	int		save_output(t_env *env, struct passwd *uid,
						struct group *gid, struct stat *buf)
{
	int			ret;
	char		*time;

	ret = 0;
	if (env->opt & L)
	{
		time = ctime((time_t *)&buf->st_mtime);
		ret = save_mod(env, buf);
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%3d ",
															buf->st_nlink);
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%s ",
															uid->pw_name);
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%s ",
															gid->gr_name);
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%6u ",
															buf->st_size);
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%.12s ",
															&time[4]);
	}
	return (ret);
}

int			save_data(t_env *env, char *path, char *file_name, t_path_r *path_r)
{
	struct stat		buf;
	struct passwd	*uid;
	struct group	*gid;
	int				ret;
	char			link[1024];

	ft_bzero(&link, sizeof(link));
	if (env->nb_files >= env->capacity)
		if (realloc_tab(env) == -1)
			exit(-1);
	if (readlink(path, link, sizeof(link)) == -1)
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
	ret = save_output(env, uid, gid, &buf);
	if (env->data[env->nb_files].output[0] == 'l' && (env->opt & L))
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%s -> %s\n",
			env->data[env->nb_files].f_name, link);
	else
		ret += ft_sprintf(&env->data[env->nb_files].output[ret], "%s\n",
										env->data[env->nb_files].f_name);
	env->nb_files++;
	return (buf.st_blocks);
}
