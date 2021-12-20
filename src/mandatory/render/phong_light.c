/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:14:15 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/20 16:13:00 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_rgb_range(int *color)
{
	int	i;

	i = 0 ;
	while (i < 3)
	{
		if (color[i] > 255)
			color[i] = 255;
		else if (color[i] < 0)
			color[i] = 0;
		i++;
	}
}

static void	get_o_ray_n_vect(t_rt *rt, t_pt_info *pt_info,
				double *o_ray, double *n_vect)
{
	sub_vect(o_ray, rt->spec->light.lp, pt_info->pt);
	if (pt_info->type == SPHERE)
		sub_vect(n_vect, pt_info->pt, pt_info->obj.sph->center);
	else if (pt_info->type == PLANE)
		vect_copy(n_vect, pt_info->obj.pl->o_vect);
	else if (pt_info->type == CYLINDER)
	{
		sub_vect(n_vect, pt_info->pt, pt_info->obj.cy->center);
		normalize_vect(n_vect);
		sub_vect(n_vect, n_vect, pt_info->obj.cy->o_vect);
	}
	else if (pt_info->type == CY_CIRCLE)
		vect_copy(n_vect, pt_info->obj.cy->circle_o_v);
	normalize_vect(n_vect);
}

static int	adjust_pl_o_vect(t_pt_info *pt_info, double *o_ray, double *n_vect)
{
	double	new_o[3];

	if (pt_info->type == PLANE)
	{
		vect_copy(new_o, n_vect);
		if (dot_product(n_vect, o_ray) < 0)
			get_pt_on_line(new_o, NULL, n_vect, -1);
		if (dot_product(new_o, pt_info->pt) > 0)
			return (1);
	}
	return (0);
}

static int	phong_rgb(t_rt *rt, t_pt_info *pt_info, int *color)
{
	double	diffuse;
	double	n_vect[3];
	double	o_ray[3];

	get_o_ray_n_vect(rt, pt_info, o_ray, n_vect);
	if (get_shadow(rt, pt_info) == SHADED
		|| adjust_pl_o_vect(pt_info, o_ray, n_vect))
		return (SHADED);
	diffuse = get_diffuse_light(n_vect, o_ray);
	color[R] = get_phong_r(rt, pt_info, diffuse);
	color[G] = get_phong_g(rt, pt_info, diffuse);
	color[B] = get_phong_b(rt, pt_info, diffuse);
	return (NOT_SHADED);
}

int	get_phong_light(t_rt *rt, t_pt_info *pt_info)
{
	int		color[3];

	if (phong_rgb(rt, pt_info, color) == SHADED)
	{
		color[R] = rt->spec->amb.ratio * (double)rt->spec->amb.color[R];
		color[G] = rt->spec->amb.ratio * (double)rt->spec->amb.color[G];
		color[B] = rt->spec->amb.ratio * (double)rt->spec->amb.color[B];
	}
	check_rgb_range(color);
	return (get_color(color, 1));
}
