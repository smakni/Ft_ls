/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <smakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 18:03:58 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/07/19 16:49:54 by smakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii_p(int c)
{
	return (c >= 0 && c <= 127);
}
