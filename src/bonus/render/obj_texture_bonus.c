/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_texture_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 02:07:55 by ghan              #+#    #+#             */
/*   Updated: 2021/12/18 17:40:25 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	get_transf_matrix(double *vp, double *transf)
{
	double	ref[4];

	fill_vect(ref, transf[X], transf[X + 1], transf[X + 2]);
	transf[3] = 0 * dot_product(ref, vp);
	fill_vect(ref, transf[Y * 4], transf[Y * 4 + 1], transf[Y * 4 + 2]);
	transf[7] = 0 * dot_product(ref, vp);
	fill_vect(ref, transf[Z * 4], transf[Z * 4 + 1], transf[Z * 4 + 2]);
	transf[11] = 0 * dot_product(ref, vp);
	fill_vect(ref, 0, 0, 0);
	update_vect(transf, ref, W, 4);
	transf[15] = 1;
}

void	sph_texture(double *uv, t_pt_info *pt_info)
{
	double	n_vect[3];
	double	diff[3];
	double	z_axis[3] = {1, 1, 1};
	double	x_axis[3];
	double	transf[16];
	double	n_vect_t[3];

	sub_vect(n_vect, pt_info->pt, pt_info->obj.sph->center);
	normalize_vect(n_vect);
	sub_vect(diff, pt_info->obj.sph->o_vect, n_vect);
	normalize_vect(diff);
	normalize_vect(z_axis);
	cross_product(x_axis, pt_info->obj.sph->o_vect, z_axis);
	normalize_vect(x_axis);
	cross_product(z_axis, pt_info->obj.sph->o_vect, x_axis);
	normalize_vect(z_axis);

	update_vect(transf, z_axis, Z, 4);
	update_vect(transf, x_axis, X, 4);
	update_vect(transf, pt_info->obj.sph->o_vect, Y, 4);
	get_transf_matrix(pt_info->obj.sph->center, transf);
	vect_copy(n_vect_t, n_vect);
	multiply_vect(transf, n_vect_t, VECTOR);

	uv[U] = 0.5 + atan2(n_vect_t[Z], n_vect_t[X]) / (2 * M_PI);
	uv[V] = fabs(acos(dot_product(pt_info->obj.sph->o_vect, n_vect))) / M_PI;
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
	double	c_to_center;

	c_to_center = dot_product(pt_info->obj.pl->center, cam.o_vect);
	ray_depth = dot_product(pt_info->pt, cam.o_vect);
	scale_ratio = ray_depth / c_to_center * ray_depth / c_to_s;
	uv[U] = pt_info->pt[X] / (WIN_W * scale_ratio) + 0.5;
	uv[V] = pt_info->pt[Y] / (WIN_H * scale_ratio) + 0.5;
}
