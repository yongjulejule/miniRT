/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:59:31 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/10 14:20:22 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	double	get_reflect_light(t_pt_info *pt_info, double *o_ray,
				double *n_vect)
{
	double	ret;
	double	reflect[3];
	double	proj[3];
	double	view[3];

	get_pt_on_line(proj, NULL, n_vect, 2 * dot_product(o_ray, n_vect));
	sub_vect(reflect, proj, o_ray);
	normalize_vect(reflect);
	if (pt_info->type == SPHERE)
		get_pt_on_line(view, NULL, pt_info->obj.sph->center, -1);
	else if (pt_info->type == PLANE)
		get_pt_on_line(view, NULL, pt_info->obj.pl->center, -1);
	else if (pt_info->type == CYLINDER || pt_info->type == CY_CIRCLE)
		get_pt_on_line(view, NULL, pt_info->obj.cy->center, -1);
	normalize_vect(view);
	ret = dot_product(reflect, view);
	if (ret < 0)
		return (0);
	return (ret);
}

int	get_phong_r(t_rt *rt, t_pt_info *pt_info, double *o_ray, double *n_vect)
{
	double	color;
	double	reflect;
	double	diffuse;
	double	amb;

	color = 0;
	reflect = get_reflect_light(pt_info, o_ray, n_vect);
	diffuse = dot_product(o_ray, n_vect);
	if (diffuse < 0)
		diffuse = 0;
	amb = (rt->spec->amb.ratio * ((double)rt->spec->amb.color[R] / 255));
	if (pt_info->type == SPHERE)
		color = ((reflect + diffuse)
				* ((double)pt_info->obj.sph->color[R] / 255)
				* ((double)rt->spec->light.color[R] / 255));
	else if (pt_info->type == PLANE)
		color = ((reflect + diffuse)
				* ((double)pt_info->obj.pl->color[R] / 255)
				* ((double)rt->spec->light.color[R] / 255));
	else if (pt_info->type == CYLINDER || pt_info->type == CY_CIRCLE)
		color = ((reflect + diffuse)
				* ((double)pt_info->obj.cy->color[R] / 255)
				* ((double)rt->spec->light.color[R] / 255));
	color = color * rt->spec->light.bright + amb;
	return ((int)(color * 255));
}

int	get_phong_g(t_rt *rt, t_pt_info *pt_info, double *o_ray, double *n_vect)
{
	double	color;
	double	reflect;
	double	diffuse;
	double	amb;

	color = 0;
	reflect = get_reflect_light(pt_info, o_ray, n_vect);
	diffuse = dot_product(o_ray, n_vect);
	if (diffuse < 0)
		diffuse = 0;
	amb = (rt->spec->amb.ratio * ((double)rt->spec->amb.color[G] / 255));
	if (pt_info->type == SPHERE)
		color = ((reflect + diffuse)
				* ((double)pt_info->obj.sph->color[G] / 255)
				* ((double)rt->spec->light.color[G] / 255));
	else if (pt_info->type == PLANE)
		color = ((reflect + diffuse)
				* ((double)pt_info->obj.pl->color[G] / 255)
				* ((double)rt->spec->light.color[G] / 255));
	else if (pt_info->type == CYLINDER || pt_info->type == CY_CIRCLE)
		color = ((reflect + diffuse)
				* ((double)pt_info->obj.cy->color[G] / 255)
				* ((double)rt->spec->light.color[G] / 255));
	color = color * rt->spec->light.bright + amb;
	return ((int)(color * 255));
}

int	get_phong_b(t_rt *rt, t_pt_info *pt_info, double *o_ray, double *n_vect)
{
	double	color;
	double	reflect;
	double	diffuse;
	double	amb;

	color = 0;
	reflect = get_reflect_light(pt_info, o_ray, n_vect);
	diffuse = dot_product(o_ray, n_vect);
	if (diffuse < 0)
		diffuse = 0;
	amb = (rt->spec->amb.ratio * ((double)rt->spec->amb.color[B] / 255));
	if (pt_info->type == SPHERE)
		color = ((reflect + diffuse)
				* ((double)pt_info->obj.sph->color[B] / 255)
				* ((double)rt->spec->light.color[B] / 255));
	else if (pt_info->type == PLANE)
		color = ((reflect + diffuse)
				* ((double)pt_info->obj.pl->color[B] / 255)
				* ((double)rt->spec->light.color[B] / 255));
	else if (pt_info->type == CYLINDER || pt_info->type == CY_CIRCLE)
		color = ((reflect + diffuse)
				* ((double)pt_info->obj.cy->color[B] / 255)
				* ((double)rt->spec->light.color[B] / 255));
	color = color * rt->spec->light.bright + amb;
	return ((int)(color * 255));
}
