/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:54:56 by smakni            #+#    #+#             */
/*   Updated: 2019/07/11 18:14:59 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <libft.h>
# include <ft_printf.h>
# include <get_next_line.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>


# define R 	1
# define L 	2
# define A 	4
# define SR 8
# define T 	16
# define ALL (FLAG1 | FLAG2 | FLAG3)

// typedef	struct s_f_info
// {
// 	char		type;
// 	char		perm[PERMISSION_LENGHT];
// 	nlink_t		n_links;
// 	char		o_name[MAX_PATH];
// 	char		o_group[MAX_PATH];
// 	off_t		size;
// 	char		tolm[MAX_TIME_LENGHT];
// 	char		name[MAX_PATH];
// }				t_f_info;

// typedef	struct	s_env
// {
// 	char 		opt;
// 	t_f_info	f_info;

// }				t_env;

void	option(char *av, char *opt);

#endif
