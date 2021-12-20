/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:59:31 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/20 15:46:08 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	get_diffuse_light(double *n_vect, double *o_ray)
{
	double	diffuse;
	double	bright;
	double	cp_ray[3];

	bright = vect_size(o_ray);
	vect_copy(cp_ray, o_ray);
	normalize_vect(cp_ray);
	diffuse = dot_product(cp_ray, n_vect) / (1 + 0.0001 * bright);
	return (diffuse);
}

double	get_reflect_light(t_pt_info *pt_i, double *o_ray, double *n_vect)
{
	double	bright;
	double	ret;
	double	reflect[3];
	double	proj[3];
	double	view[3];

	bright = vect_size(o_ray);
	get_pt_on_line(proj, NULL, n_vect, 2 * dot_product(o_ray, n_vect));
	sub_vect(reflect, proj, o_ray);
	get_pt_on_line(view, NULL, pt_i->pt, -1);
	normalize_vect(view);
	normalize_vect(reflect);
	ret = dot_product(reflect, view) / (1 + 0.0001 * bright);
	if (dot_product(n_vect, reflect) < 0)
		return (0);
	if (signbit(ret))
		return (0);
	return (ret);
}

double	get_phong_r(t_l_lst *cur, t_pt_info *pt_i, double diffuse,
			double reflect)
{
	double	color;

	color = 0;
	if (signbit(diffuse))
		diffuse = 0;
	color = ((reflect + diffuse)
			* ((double)pt_i->color[R] / 255)
			* ((double)cur->color[R] / 255));
	return (color * cur->bright);
}

double	get_phong_g(t_l_lst *cur, t_pt_info *pt_i, double diffuse,
			double reflect)
{
	double	color;

	color = 0;
	if (signbit(diffuse))
		diffuse = 0;
	color = ((reflect + diffuse)
			* ((double)pt_i->color[G] / 255)
			* ((double)cur->color[G] / 255));
	return (color * cur->bright);
}

double	get_phong_b(t_l_lst *cur, t_pt_info *pt_i, double diffuse,
			double reflect)
{
	double	color;

	color = 0;
	if (signbit(diffuse))
		diffuse = 0;
	color = ((reflect + diffuse)
			* ((double)pt_i->color[B] / 255)
			* ((double)cur->color[B] / 255));
	return (color * cur->bright);
}
