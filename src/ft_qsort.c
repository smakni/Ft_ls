/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabri <sabri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 15:15:48 by sabri             #+#    #+#             */
/*   Updated: 2019/07/26 16:57:57 by sabri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_qsort_data(t_data *data, int first, int last)
{
	int		i;
	int		j;
	int 	pivot;
	t_data	tmp;

   if (first < last)
   {
		pivot = first;
		i = first;
		j = last;
		while(i < j)
		{
			while (data[i].time >= data[pivot].time && i < last)
            	i++;
         	while (data[j].time < data[pivot].time)
            	j--;
			if (i < j) 
			{
            	tmp = data[i];
            	data[i] = data[j];
            	data[j] = tmp;
         	}
      	}
		tmp = data[pivot];
    	data[pivot] = data[j];
      	data[j] = tmp;
      	ft_qsort_data(data, first, j - 1);
     	ft_qsort_data(data, j + 1, last);
   }
}

void	ft_qsort_dir(t_path_r *path_r, int first, int last)
{
	int		i;
	int		j;
	int 	pivot;
	t_path	tmp;

   if (first < last)
   {
		pivot = first;
		i = first;
		j = last;
		while(i < j)
		{
			while (path_r->path_lst[i].time >= path_r->path_lst[pivot].time && i < last)
            	i++;
         	while (path_r->path_lst[j].time < path_r->path_lst[pivot].time)
            	j--;
			if (i < j) 
			{
            	tmp = path_r->path_lst[i];
            	path_r->path_lst[i] = path_r->path_lst[j];
            	path_r->path_lst[j] = tmp;
         	}
      	}
		tmp = path_r->path_lst[pivot];
    	path_r->path_lst[pivot] = path_r->path_lst[j];
      	path_r->path_lst[j] = tmp;
      	ft_qsort_dir(path_r, first, j - 1);
     	ft_qsort_dir(path_r, j + 1, last);
   }
}