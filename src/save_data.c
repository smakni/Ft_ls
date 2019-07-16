/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:37:58 by smakni            #+#    #+#             */
/*   Updated: 2019/07/16 15:55:41 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static	int		save_mod(t_env *env, struct stat *buf)
{
	ft_memset(env->data[env->nb_files].output, '-', 10);
	if ((buf->st_mode & S_IFMT) == S_IFDIR)
		env->data[env->nb_files].output[0] = 'd';
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

static	void	save_output(t_env *env, struct passwd *uid,
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
	ft_sprintf(&env->data[env->nb_files].output[ret], "%s\n",
										env->data[env->nb_files].f_name);
}

void			save_data(t_env *env, char *path, char *file_name)
{
	struct stat		buf;
	struct passwd	*uid;
	struct group	*gid;

	if (env->nb_files >= env->capacity)
		if (realloc_tab(env) == -1)
			exit(-1);
	if ((stat(path, &buf)) == -1)
	{
		ft_printf("print_stat : acces impossible a %s\n", path);
		return ;
	}
	env->data[env->nb_files].f_name = file_name;
	env->data[env->nb_files].time = buf.st_mtime;
	uid = getpwuid(buf.st_uid);
	gid = getgrgid(uid->pw_gid);
	save_output(env, uid, gid, &buf);
	env->nb_files++;
}
