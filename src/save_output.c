/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:49:51 by smakni            #+#    #+#             */
/*   Updated: 2019/08/08 00:39:22 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		save_output(t_env *e)
{
	int			i;
	int			ret;
	char		*time;

	i = 0;
	while (i < e->nb_files)
	{
		ret = e->max_width.perm;
		if (e->opt & L)
		{
			time = ctime((time_t *)&e->data[i].time);
			ret += e->max_width.l - e->data[i].width.l + 2;
			ret += ft_sprintf(&e->data[i].output[ret], "%d", e->data[i].nb_link);
			e->data[i].output[ret++] = ' ';
			ret += e->max_width.un - e->data[i].width.un;
			ret += ft_sprintf(&e->data[i].output[ret], "%s", e->data[i].pw_name);
			e->data[i].output[ret++] = ' ';
			ret += e->max_width.gn - e->data[i].width.gn + 1;
			ret += ft_sprintf(&e->data[i].output[ret], "%s", e->data[i].gr_name);
			e->data[i].output[ret++] = ' ';
			ret += e->max_width.s - e->data[i].width.s + 1;
			ret += ft_sprintf(&e->data[i].output[ret], "%u ", e->data[i].st_size);
			ret += ft_sprintf(&e->data[i].output[ret], "%.12s ", &time[4]); // check leak here
		}
		if (e->data[i].output[0] == 'l' && (e->opt & L))
			ret += ft_sprintf(&e->data[i].output[ret], "%s -> %s\n",
				e->data[i].f_name, e->data[i].link);
		else
			ret += ft_sprintf(&e->data[i].output[ret], "%s\n",
											e->data[i].f_name);
		i++;
	}
	ft_bzero(&e->max_width, sizeof(t_width));
	return (ret);
}
