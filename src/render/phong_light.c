/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:14:15 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/09 12:20:09 by yongjule         ###   ########.fr       */
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

// static void	each_rgb_phong(int *color, double pre_cal
// 			, t_rt *rt, t_pt_info *pt_i)
// {
// 	int		i;
// 	double	dst[3];
// 	double	reflect[3];

// 	i = 0;
// 	pre_cal = dot_product(o_ray, n_vect) * rt->spec->light.bright;
// 	get_pt_on_line(dst, NULL, n_vect, 2 * dot_product(o_ray, n_vect));
// 	fill_vect(cam, -1 * pt_i->obj.pl->center[X], -1 * pt_i->obj.pl->center[Y], -1 * pt_i->obj.pl->center[Z]);
// 	sub_vect(reflect, dst, ray)
// 	ref = dot_product(dst, reflect) * (double)rt->light.color[i];
// 	if (pre_cal < 0)
// 		pre_cal = 0;
// 	while (i < 3)
// 	{
// 		if (pt_i->type == SPHERE)
// 			color[i] = ((pre_cal * (double)rt->spec->light.color[i] / 255
// 						* (double)pt_i->obj.sph->color[i] / 255)
// 					+ (rt->spec->amb.ratio * (double)rt->spec->amb.color[i]
// 						/ 255)) * 255;
// 		else if (pt_i->type == PLANE)
// 			color[i] = ((pre_cal * (double)rt->spec->light.color[i] / 255
// 						* (double)pt_i->obj.pl->color[i] / 255)
// 					+ (rt->spec->amb.ratio * (double)rt->spec->amb.color[i]
// 						/ 255)) * 255;
// 		else if (pt_i->type == CYLINDER || pt_i->type == CY_CIRCLE)
// 			color[i] = ((pre_cal * (double)rt->spec->light.color[i] / 255
// 						* (double)pt_i->obj.cy->color[i] / 255)
// 					+ (rt->spec->amb.ratio * (double)rt->spec->amb.color[i]
// 						/ 255)) * 255;
// 		i++;
// 	}
// }

static int	phong_rgb(t_rt *rt, t_pt_info *pt_info, int *color)
{
	int		shadow;
	double	n_vect[3];
	double	o_ray[3];

	sub_vect(o_ray, rt->spec->light.lp, pt_info->pt);
	normalize_vect(o_ray);
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
		vect_copy(n_vect, pt_info->c_o_vect);
	normalize_vect(n_vect);
	shadow = get_shadow(rt, pt_info);
	if (shadow == SHADED)
		return (SHADED);
	color[R] = get_phong_r(rt, pt_info, o_ray, n_vect);
	color[G] = get_phong_g(rt, pt_info, o_ray, n_vect);
	color[B] = get_phong_b(rt, pt_info, o_ray, n_vect);
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
