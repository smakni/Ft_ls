/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:49:51 by smakni            #+#    #+#             */
/*   Updated: 2019/09/24 13:57:49 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static long convert_data_to_second(int year, int month, int day, int hour, int s)
{
	double	years_to_s;
	int		month_to_s;
	int		day_to_s;
	int		hour_to_s;

	// years_to_s = year * 31536000;
	month_to_s = month * 2592000;
	day_to_s = day * 86400;
	hour_to_s = hour * 60;
	long tmp = years_to_s + month_to_s + day_to_s + hour_to_s + s;
	return (tmp);
}

static void	write_type(t_env *e, struct stat *buf)
{
	ft_memset(e->data[e->nb_files].output, ' ', 4092);
	ft_memset(e->data[e->nb_files].output, '-', 10);
	if ((buf->st_mode & S_IFMT) == S_IFDIR)
		e->data[e->nb_files].output[0] = 'd';
	else if ((buf->st_mode & S_IFMT) == S_IFLNK)
		e->data[e->nb_files].output[0] = 'l';
	else if ((buf->st_mode & S_IFMT) == S_IFSOCK)
		e->data[e->nb_files].output[0] = 's';
	else if ((buf->st_mode & S_IFMT) == S_IFCHR)
		e->data[e->nb_files].output[0] = 'c';
	else if ((buf->st_mode & S_IFMT) == S_IFIFO)
		e->data[e->nb_files].output[0] = 'p';
	else if ((buf->st_mode & S_IFMT) == S_IFLNK)
		e->data[e->nb_files].output[0] = 'n';
}

int			write_mod(t_env *e, struct stat *buf, char *path)
{
	char	namebuf[MAX_FSIZE];

	(void)path;
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
	char 		*date_str;
	long		time_secondes;
	int			tmp;
	time_t 		today;
    struct tm	tm;

	today = time(NULL);
	// tm = *localtime(&today);
	tm = *localtime((time_t *)&e->data[i].time);
	date_str = ctime((time_t *)&e->data[i].time);
	time_secondes = convert_data_to_second(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
						tm.tm_hour, tm.tm_min * 60 + tm.tm_sec);
	ft_printf("Time: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	ft_printf("time_toSeconds: %ld\n", time_secondes);
	ret += e->max_width.l - e->data[i].width.l + SPE;
	ret += ft_sprintf(&e->data[i].output[ret], "%d", e->data[i].nb_link);
	e->data[i].output[ret++] = ' ';
	ft_strncpy(&e->data[i].output[ret], e->data[i].pw_name, e->data[i].width.un);
	ret += e->max_width.un + SPE;
	ft_strncpy(&e->data[i].output[ret], e->data[i].gr_name, e->data[i].width.gn);
	ret += e->max_width.gn + SPE;
	ret += e->max_width.s - e->data[i].width.s;
	ret += ft_sprintf(&e->data[i].output[ret], "%u ", e->data[i].st_size);
	ret += ft_sprintf(&e->data[i].output[ret], "%.7s", &date_str[4]);
	if ((tmp = ft_atoi(&date_str[20])) != CURRENT_YEAR) 						// >> less then 6 month
		ret += ft_sprintf(&e->data[i].output[ret], " %d ", tmp);
	else
		ret += ft_sprintf(&e->data[i].output[ret], "%.5s ", &date_str[11]);
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
