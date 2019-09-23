/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:49:51 by smakni            #+#    #+#             */
/*   Updated: 2019/09/23 10:42:00 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

// int	write_details(t_env *e, int i, int ret)
// {
// 	char * time;

// 	time = ctime((time_t *)&e->data[i].time);
// 	ret += e->max_width.l - e->data[i].width.l + SPE + 1;
// 	ret += ft_sprintf(&e->data[i].output[ret], "%d", e->data[i].nb_link);
// 	e->data[i].output[ret++] = ' ';
// 	ret += e->max_width.un - e->data[i].width.un;
// 	ret += ft_sprintf(&e->data[i].output[ret], "%s", e->data[i].pw_name);
// 	e->data[i].output[ret++] = ' ';
// 	ret += e->max_width.gn - e->data[i].width.gn + SPE;
// 	ret += ft_sprintf(&e->data[i].output[ret], "%s", e->data[i].gr_name);
// 	e->data[i].output[ret++] = ' ';
// 	ret += e->max_width.s - e->data[i].width.s + SPE;
// 	ret += ft_sprintf(&e->data[i].output[ret], "%u ", e->data[i].st_size);
// 	ret += ft_sprintf(&e->data[i].output[ret], "%.12s ", &time[4]);
// 	return (ret);
// }

static void	write_type(t_env *e, struct stat *buf)
{
	ft_memset(e->data[e->nb_files].output, ' ', 4092);
	ft_memset(e->data[e->nb_files].output, '-', 10);
	if ((buf->st_mode & S_IFMT) == S_IFDIR)
		e->data[e->nb_files].output[0] = 'd';
	else if ((buf->st_mode & S_IFMT) == S_IFLNK)
		e->data[e->nb_files].output[0] = 'l';
}

int			write_mod(t_env *e, struct stat *buf, char *path)
{
	char	namebuf[MAX_FSIZE];

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

int		write_details(t_env *e, int i, int ret)
{
	char 	*time;
	int		tmp;

	time = ctime((time_t *)&e->data[i].time);
	ret += e->max_width.l - e->data[i].width.l + SPE;
	ret += ft_sprintf(&e->data[i].output[ret], "%d", e->data[i].nb_link);
	e->data[i].output[ret++] = ' ';
	ft_strncpy(&e->data[i].output[ret], e->data[i].pw_name, e->data[i].width.un);
	ret += e->max_width.un + SPE;
	ft_strncpy(&e->data[i].output[ret], e->data[i].gr_name, e->data[i].width.gn);
	ret += e->max_width.gn + SPE;
	ret += e->max_width.s - e->data[i].width.s;
	ret += ft_sprintf(&e->data[i].output[ret], "%u ", e->data[i].st_size);
	ret += ft_sprintf(&e->data[i].output[ret], "%.7s", &time[4]);
	if ((tmp = ft_atoi(&time[20])) != CURRENT_YEAR)
		ret += ft_sprintf(&e->data[i].output[ret], " %d ", tmp);
	else
		ret += ft_sprintf(&e->data[i].output[ret], "%.5s ", &time[11]);
	return (ret);
}

void	write_output(t_env *e)
{
	int	i;
	int	ret;

	i = 0;
	while (i < e->nb_files)
	{
		ret = e->max_width.perm;
		if (e->opt & L)
			ret = write_details(e, i, ret);
		if (e->data[i].output[0] == 'l' && (e->opt & L))
			ft_sprintf(&e->data[i].output[ret], "%s -> %s",
				e->data[i].f_name, e->data[i].link);
		else
			ft_sprintf(&e->data[i].output[ret], "%s",
											e->data[i].f_name);
		i++;
	}
	ft_bzero(&e->max_width, sizeof(t_width));
}
