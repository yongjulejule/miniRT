/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_texture_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 02:07:55 by ghan              #+#    #+#             */
/*   Updated: 2021/12/18 02:21:49 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	sph_texture(double *uv, t_pt_info *pt_info)
{
	double	n_vect[3];

	if (pt_info->type == SPHERE)
	{
		sub_vect(n_vect, pt_info->obj.sph->center, pt_info->pt);
		normalize_vect(n_vect);
		uv[U] = 0.5 + atan2(n_vect[Z], n_vect[X]) / (2 * M_PI);
		uv[V] = 0.5 - asin(n_vect[Y]) / M_PI;
	}
}

void	cy_texture(double *uv, t_pt_info *pt_info)
{
	double	n_vect[3];
	double	center_to_pt[3];

	sub_vect(center_to_pt, pt_info->pt, pt_info->obj.cy->center);
	normalize_vect(n_vect);
	sub_vect(n_vect, center_to_pt, pt_info->obj.cy->o_vect);
	uv[U] = 0.5 + atan2(n_vect[Z], n_vect[X]) / (2 * M_PI);
	uv[V] = dot_product(center_to_pt, pt_info->obj.cy->o_vect)
		/ pt_info->obj.cy->height;
}

void	cn_texture(double *uv, t_pt_info *pt_info)
{
	double	n_vect[3];
	double	center_to_pt[3];
	double	vert[3];
	double	hori[3];

	sub_vect(vert, pt_info->pt, pt_info->obj.cn->center);
	normalize_vect(vert);
	sub_vect(vert, vert, pt_info->obj.cn->o_vect);
	get_pt_on_line(vert, NULL, vert, pt_info->obj.cn->height);
	get_pt_on_line(hori, NULL, pt_info->obj.cn->o_vect,
		pt_info->obj.cn->radius);
	sub_vect(center_to_pt, pt_info->pt, pt_info->obj.cn->center);
	n_vect[X] = vert[X] + hori[X];
	n_vect[Y] = vert[Y] + hori[Y];
	n_vect[Z] = vert[Z] + hori[Z];
	uv[U] = 0.5 + atan2(n_vect[Z], n_vect[X]) / (2 * M_PI);
	uv[V] = dot_product(center_to_pt, pt_info->obj.cn->o_vect)
		/ pt_info->obj.cn->height;
}
