/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:00:34 by smakni            #+#    #+#             */
/*   Updated: 2019/07/11 18:00:49 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	option(char *av, char *opt)
{
	if (ft_strchr(av, 'R') != 0)
		*opt |= 1;
	if (ft_strchr(av, 'l') != 0)
		*opt |= 2;
	if (ft_strchr(av, 'a') != 0)
		*opt |= 4;
	if (ft_strchr(av, 'r') != 0)
		*opt |= 8;
	if (ft_strchr(av, 't') != 0)
		*opt |= 16;
}
