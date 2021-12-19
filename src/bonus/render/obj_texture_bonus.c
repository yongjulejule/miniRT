/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_texture_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 02:07:55 by ghan              #+#    #+#             */
/*   Updated: 2021/12/19 15:33:17 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	sph_texture(double *uv, t_pt_info *pt_info)
{
	double	n_vect[3];
	double	cur_vect[3];
	double	angle[3];

	get_pt_on_line(angle, NULL, pt_info->obj.sph->o_vect, -1);
	sub_vect(n_vect, pt_info->pt, pt_info->obj.sph->center);
	normalize_vect(n_vect);
	rotate_vect(cur_vect, n_vect, angle);
	normalize_vect(cur_vect);
	uv[U] = 0.5 + (atan2(cur_vect[Y], cur_vect[X]) / (2 * M_PI));
	uv[V] = acos(cur_vect[Z]) / M_PI;
}

void	cy_texture(double *uv, t_pt_info *pt_info)
{
	double	n_vect[3];
	double	center_to_pt[3];
	double	center_to_pt_n[3];

	sub_vect(center_to_pt_n, pt_info->pt, pt_info->obj.cy->center);
	vect_copy(center_to_pt, center_to_pt_n);
	normalize_vect(center_to_pt_n);
	sub_vect(n_vect, center_to_pt_n, pt_info->obj.cy->o_vect);
	normalize_vect(n_vect);
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
	normalize_vect(n_vect);
	uv[U] = 0.5 + atan2(n_vect[Z], n_vect[X]) / (2 * M_PI);
	uv[V] = dot_product(center_to_pt, pt_info->obj.cn->o_vect)
		/ pt_info->obj.cn->height;
}

void	pl_texture(double *uv, t_pt_info *pt_info, t_cam cam, double c_to_s)
{
	double	ray_depth;
	double	scale_ratio;

	ray_depth = dot_product(pt_info->pt, cam.o_vect);
	scale_ratio = ray_depth / c_to_s;
	uv[U] = pt_info->pt[X] / (WIN_W * scale_ratio) + 0.5;
	uv[V] = pt_info->pt[Y] / (WIN_H * scale_ratio) + 0.5;
}
