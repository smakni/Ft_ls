/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:56 by smakni            #+#    #+#             */
/*   Updated: 2019/07/08 18:36:49 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <libft.h>
#include <ft_printf.h>
#include <get_next_line.h>
#include <sys/dir.h>
#include <sys/stat.h>

#define		ERROR 		-1
#define		CAPACITY	1024

typedef	struct	s_env
{
	DIR				*dir[CAPACITY];
	int				nb_dir;
//	struct dirent 	*dirp[CAPACITY];
}				t_env;

#endif
