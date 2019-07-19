/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 12:48:35 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/07/19 15:02:48 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset_p(void *dest, int value, size_t count)
{
	size_t i;

	i = 0;
	while (i < count)
	{
		((char*)dest)[i] = (unsigned char)(value);
		i++;
	}
	return (dest);
}
