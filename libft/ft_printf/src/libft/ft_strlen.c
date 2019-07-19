/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:06:47 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/07/19 16:50:06 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>
#include <limits.h>

size_t	ft_strlen_p(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_get_mb_size(const wchar_t *s, int *error)
{
	size_t	i;
	size_t	byte_count;
	char	buffer[MB_LEN_MAX];
	char	mbchar_size;

	i = 0;
	byte_count = 0;
	while (s[i] != '\0')
	{
		mbchar_size = ft_wctomb(buffer, s[i]);
		if (mbchar_size == 0)
		{
			*error = 1;
			return (0);
		}
		byte_count += mbchar_size;
		i++;
	}
	return (byte_count);
}

size_t	ft_get_fitting_mb_size(wchar_t *s, size_t max_size, int *error)
{
	size_t	i;
	size_t	byte_count;
	int		mbchar_size;
	char	buffer[MB_LEN_MAX];

	i = 0;
	byte_count = 0;
	while (s[i] != '\0')
	{
		mbchar_size = ft_wctomb(buffer, s[i]);
		if (mbchar_size == 0)
		{
			*error = 1;
			return (0);
		}
		byte_count += mbchar_size;
		if (byte_count == max_size)
			return (byte_count);
		if (byte_count > max_size)
			return (byte_count - mbchar_size);
		i++;
	}
	return (byte_count);
}
