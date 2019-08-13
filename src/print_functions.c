/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 14:40:23 by smakni            #+#    #+#             */
/*   Updated: 2019/08/13 18:04:37 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	print_data(t_env *e)
{
	int i;

	i = 0;
	// alphaqsort_data(e->data, 0, e->nb_files - 1);
	// if (e->opt & T)
	// 	qsort_data(e->data, 0, e->nb_files - 1);
	if (e->opt & SR)
	{
		i = e->nb_files - 1;
		while (i >= 0)
		{	
			ft_printf("%s", e->data[i].output);
			i--;
		}
	}
	else
		while (i < e->nb_files)
		{
			ft_printf("%s", e->data[i].output);
			i++;
		}
}

void	print_path(t_env *e, char *path)
{
	if (e->cursor > 0)
		ft_putendl("");
	if (e->nb_files > 0 && e->cursor > 0)
		ft_printf("%s:\n", path);
	else if (e->cursor > 0)
		ft_printf("%s\n", path);
}
