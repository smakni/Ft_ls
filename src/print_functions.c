/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 14:40:23 by smakni            #+#    #+#             */
/*   Updated: 2019/09/19 14:55:28 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	print_path(t_env *e, char *path)
{
	if (e->cursor == 0)
	{
		if (e->nb_arg > 1)
			ft_printf("%s:\n", path);
	}
	else if ((e->cursor > 0 && (e->opt && R)) || e->nb_arg > 1)
		ft_printf("\n%s:\n", path);
}

void	print_data(t_env *e, char *path)
{
	int i;

	i = 0;
	print_path(e, path);
	if (e->opt & L && e->nb_files > 0)
		ft_printf("total %d\n", e->total);
	if (e->opt & SR)
	{
		i = e->nb_files - 1;
		while (i >= 0)
			ft_printf("%s\n", e->data[i--].output);
	}
	else
		while (i < e->nb_files)
			ft_printf("%s\n", e->data[i++].output);
}
