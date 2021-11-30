/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:27:04 by ghan              #+#    #+#             */
/*   Updated: 2021/11/30 12:38:53 by ghan             ###   ########.fr       */
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

int	color_per_pixel_sph(t_sph *sph, t_light l_info)
{
	double	d;
	double	ratio;
	int		color[3];

	d = sqrt(pow(sph->center[X] - l_info.lp[X], 2)
			+ pow(sph->center[Y] - l_info.lp[Y], 2)
			+ pow(sph->center[Z] - l_info.lp[Z], 2));
	ratio = l_info.bright / pow(d, 2);
	color[X] = sph->color[X] * ratio + l_info.color[X] * (1 - ratio);
	color[Y] = sph->color[Y] * ratio + l_info.color[Y] * (1 - ratio);
	color[Z] = sph->color[Z] * ratio + l_info.color[Z] * (1 - ratio);
	return (get_color(color, 1));
}
