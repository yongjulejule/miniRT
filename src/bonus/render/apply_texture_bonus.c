/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:39:27 by ghan              #+#    #+#             */
/*   Updated: 2021/12/18 02:22:42 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	apply_checker(t_pt_info *pt_info)
{
	double	sines;
	double	div;

	div = 100;
	if (pt_info->type == PLANE)
		div = 400;
	else if (pt_info->type == SPHERE)
		div = pt_info->obj.sph->radius / 4;
	else if (pt_info->type == CYLINDER)
		div = pt_info->obj.cy->radius / 4;
	else if (pt_info->type == CONE)
		div = pt_info->obj.cn->radius / 4;
	sines = sin(pt_info->pt[X] / div) * sin(pt_info->pt[Y] / div)
		* sin(pt_info->pt[Z] / div);
	if (!signbit(sines))
		ft_bzero(pt_info->color, sizeof(int) * 3);
	else
	{
		pt_info->color[R] = 255;
		pt_info->color[G] = 255;
		pt_info->color[B] = 255;
	}
}

void	apply_texture(t_pt_info *pt_info)
{
	double	uv[2];
	int		idx;

	if (pt_info->type == SPHERE)
		sph_texture(uv, pt_info);
	else if (pt_info->type == CYLINDER)
		cy_texture(uv, pt_info);
	else if (pt_info->type == CONE)
		cn_texture(uv, pt_info);
	idx = pt_info->ppm.size[X] * 3 * (int)(uv[V] * (pt_info->ppm.size[Y] - 1))
		+ 3 * (int)(uv[U] * (pt_info->ppm.size[X] - 1));
	pt_info->color[R] = pt_info->ppm.color_arr[idx];
	pt_info->color[G] = pt_info->ppm.color_arr[idx + 1];
	pt_info->color[B] = pt_info->ppm.color_arr[idx + 2];
}
