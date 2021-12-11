/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:27:04 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 15:44:42 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(int *color, double ratio)
{
	return ((int)(color[R] * ratio) << 16
			| (int)(color[G] * ratio) << 8 | (int)(color[B] * ratio));
}

int	cur_pixel(t_rt *rt, int w, int h)
{
	return ((h * rt->obj_img.width + w * rt->obj_img.bpp / 8) / 4);
}

void	copy_color(int *dst, int *src)
{
	dst[R] = src[R];
	dst[G] = src[G];
	dst[B] = src[B];
}
