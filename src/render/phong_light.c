/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:14:15 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/01 17:19:21 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* get RGB value and make it int */

void	sub_vect(double *vect, double *dst, double *src)
{
	vect[X] = dst[X] - src[X];
	vect[Y] = dst[Y] - src[Y];
	vect[Z] = dst[Z] - src[Z];
}

int	get_phong_light_sph(t_rt *rt, t_pt_info *pt_info)
{
	int		color[3];
	int		shadow;
	double	n_vect[3];
	double	o_ray[3];

	sub_vect(n_vect, pt_info->pt, rt->spec->obj_lst->obj.sph->center);
	normalize_vect(n_vect);
	sub_vect(o_ray, rt->spec->light.lp, pt_info->pt);
	normalize_vect(o_ray);
	shadow = 1;
	color[R] = shadow * (dot_product(o_ray, n_vect) * R) + rt->spec->amb.ratio * rt->spec->amb.color[R];
	color[G] = shadow * (dot_product(o_ray, n_vect) * B) + rt->spec->amb.ratio * rt->spec->amb.color[G];
	color[B] = shadow * (dot_product(o_ray, n_vect) * G) + rt->spec->amb.ratio * rt->spec->amb.color[B];
	fprintf(stderr, "color is : %#x",get_color(color, 1));
	return (get_color(color, 1));
}