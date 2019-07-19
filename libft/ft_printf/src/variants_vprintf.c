/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variants_vprintf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:00:11 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/07/19 15:02:34 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <array.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

int		ft_vprintf(const char *string, va_list list)
{
	t_array	output;
	int		ret;

	ret = real_printf(&output, string, list);
	write(1, output.data, (size_t)output.size);
	free(output.data);
	return (ret);
}

int		ft_vsprintf(char *str, const char *format, va_list list)
{
	t_array	output;
	int		ret;

	ret = real_printf(&output, format, list);
	ft_memcpy_p(str, output.data, (size_t)output.size);
	free(output.data);
	return (ret);
}

int		ft_vsnprintf(char *str, size_t size, const char *format, va_list list)
{
	t_array	output;
	int		ret;

	ret = real_printf(&output, format, list);
	ft_memcpy_p(str, output.data, size);
	free(output.data);
	return (ret);
}

int		ft_vasprintf(char **str, const char *format, va_list list)
{
	t_array	output;
	int		ret;

	ret = real_printf(&output, format, list);
	*str = output.data;
	return (ret);
}

int		ft_vdprintf(int fd, const char *string, va_list list)
{
	t_array	output;
	int		ret;

	ret = real_printf(&output, string, list);
	write(fd, output.data, (size_t)output.size);
	free(output.data);
	return (ret);
}
