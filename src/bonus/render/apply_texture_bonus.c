/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:39:27 by ghan              #+#    #+#             */
/*   Updated: 2021/12/19 11:32:52 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	apply_checker(t_pt_info *pt_info)
{
	double	sines;
	double	div;

	div = 100;
	sines = sin(pt_info->pt[X] / div) * sin(pt_info->pt[Y] / div);
	if (!signbit(sines))
		ft_bzero(pt_info->color, sizeof(int) * 3);
	else
	{
		pt_info->color[R] = 255;
		pt_info->color[G] = 255;
		pt_info->color[B] = 255;
	}
}

void	apply_texture(t_pt_info *pt_i, t_cam cam, double c_to_s)
{
	double	uv[2];
	int		idx;

	if (pt_i->type == SPHERE)
		sph_texture(uv, pt_i);
	else if (pt_i->type == CYLINDER)
		cy_texture(uv, pt_i);
	else if (pt_i->type == CONE)
		cn_texture(uv, pt_i);
	else if (pt_i->type == PLANE)
		pl_texture(uv, pt_i, cam, c_to_s);
	if (uv[U] >= 0 && uv[U] <= 1 && uv[V] >= 0 && uv[V] <= 1)
	{
		idx = pt_i->ppm.size[X] * 3 * (int)(uv[V] * (pt_i->ppm.size[Y] - 1))
			+ 3 * (int)(uv[U] * (pt_i->ppm.size[X] - 1));
		pt_i->color[R] = pt_i->ppm.color_arr[idx];
		pt_i->color[G] = pt_i->ppm.color_arr[idx + 1];
		pt_i->color[B] = pt_i->ppm.color_arr[idx + 2];
	}
}
