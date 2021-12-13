/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:59:31 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/13 22:08:00 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static	double	get_reflect_light(t_pt_info *pt_i, double *o_ray,
				double *n_vect)
{
	double	ret;
	double	reflect[3];
	double	proj[3];
	double	view[3];

	get_pt_on_line(proj, NULL, n_vect, 2 * dot_product(o_ray, n_vect));
	sub_vect(reflect, proj, o_ray);
	normalize_vect(reflect);
	if (pt_i->type == SPHERE)
		get_pt_on_line(view, NULL, pt_i->obj.sph->center, -1);
	else if (pt_i->type == PLANE)
		get_pt_on_line(view, NULL, pt_i->obj.pl->center, -1);
	else if (pt_i->type == CYLINDER || pt_i->type == CY_CIRCLE)
		get_pt_on_line(view, NULL, pt_i->obj.cy->center, -1);
	else if (pt_i->type == CONE || pt_i->type == CN_CIRCLE)
		get_pt_on_line(view, NULL, pt_i->obj.cn->center, -1);
	normalize_vect(view);
	ret = dot_product(reflect, view);
	if (ret < 0)
		return (0);
	return (ret);
}

double	get_phong_r(t_l_lst *cur, t_pt_info *pt_i, double *o_ray,
			double *n_vect)
{
	double	color;
	double	reflect;
	double	diffuse;

	color = 0;
	reflect = get_reflect_light(pt_i, o_ray, n_vect);
	diffuse = dot_product(o_ray, n_vect);
	if (diffuse < 0)
		diffuse = 0;
	if (pt_i->type == SPHERE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.sph->color[R] / 255)
				* ((double)cur->color[R] / 255));
	else if (pt_i->type == PLANE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.pl->color[R] / 255)
				* ((double)cur->color[R] / 255));
	else if (pt_i->type == CYLINDER || pt_i->type == CY_CIRCLE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.cy->color[R] / 255)
				* ((double)cur->color[R] / 255));
	else if (pt_i->type == CONE || pt_i->type == CN_CIRCLE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.cn->color[R] / 255)
				* ((double)cur->color[R] / 255));
	return (color * cur->bright);
}

double	get_phong_g(t_l_lst *cur, t_pt_info *pt_i, double *o_ray,
			double *n_vect)
{
	double	color;
	double	reflect;
	double	diffuse;

	color = 0;
	reflect = get_reflect_light(pt_i, o_ray, n_vect);
	diffuse = dot_product(o_ray, n_vect);
	if (diffuse < 0)
		diffuse = 0;
	if (pt_i->type == SPHERE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.sph->color[G] / 255)
				* ((double)cur->color[G] / 255));
	else if (pt_i->type == PLANE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.pl->color[G] / 255)
				* ((double)cur->color[G] / 255));
	else if (pt_i->type == CYLINDER || pt_i->type == CY_CIRCLE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.cy->color[G] / 255)
				* ((double)cur->color[G] / 255));
	else if (pt_i->type == CONE || pt_i->type == CN_CIRCLE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.cn->color[R] / 255)
				* ((double)cur->color[R] / 255));
	return (color * cur->bright);
}

double	get_phong_b(t_l_lst *cur, t_pt_info *pt_i, double *o_ray,
			double *n_vect)
{
	double	color;
	double	reflect;
	double	diffuse;

	color = 0;
	reflect = get_reflect_light(pt_i, o_ray, n_vect);
	diffuse = dot_product(o_ray, n_vect);
	if (diffuse < 0)
		diffuse = 0;
	if (pt_i->type == SPHERE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.sph->color[B] / 255)
				* ((double)cur->color[B] / 255));
	else if (pt_i->type == PLANE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.pl->color[B] / 255)
				* ((double)cur->color[B] / 255));
	else if (pt_i->type == CYLINDER || pt_i->type == CY_CIRCLE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.cy->color[B] / 255)
				* ((double)cur->color[B] / 255));
	else if (pt_i->type == CONE || pt_i->type == CN_CIRCLE)
		color = ((reflect + diffuse)
				* ((double)pt_i->obj.cn->color[R] / 255)
				* ((double)cur->color[R] / 255));
	return (color * cur->bright);
}
