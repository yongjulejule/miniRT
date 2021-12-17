/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cn_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:19:16 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/17 20:59:31 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static double	get_cn_b(double *r, t_cn *cn, double *o, double under)
{
	return (-2 * o[X] * r[X] * pow(cn->o_vect[X], 2) + 2 * o[X] * r[X]
		* under - 2 * o[X] * r[Y] * cn->o_vect[X] * cn->o_vect[Y]
		- 2 * o[X] * r[Z] * cn->o_vect[X] * cn->o_vect[Z] - 2 * o[Y] * r[X]
		* cn->o_vect[X] * cn->o_vect[Y] - 2 * o[Y] * r[Y]
		* pow(cn->o_vect[Y], 2) + 2 * o[Y] * r[Y] * under
		- 2 * o[Y] * r[Z] * cn->o_vect[Y] * cn->o_vect[Z]
		- 2 * o[Z] * r[X] * cn->o_vect[X] * cn->o_vect[Z] - 2 * o[Z] * r[Y]
		* cn->o_vect[Y] * cn->o_vect[Z] - 2 * o[Z] * r[Z]
		* pow(cn->o_vect[Z], 2) + 2 * o[Z] * r[Z] * under);
}

static double	get_cn_c(t_cn *cn, double *o, double under)
{
	return (pow(o[X] * cn->o_vect[X], 2) - pow(o[X], 2) * under + 2 * o[X]
		* o[Y] * cn->o_vect[X] * cn->o_vect[Y] + 2 * o[X] * o[Z]
		* cn->o_vect[X] * cn->o_vect[Z] + pow(o[Y] * cn->o_vect[Y], 2)
		- pow(o[Y], 2) * under + 2 * o[Y] * o[Z] * cn->o_vect[Y]
		* cn->o_vect[Z] + pow(o[Z] * cn->o_vect[Z], 2)
		- pow(o[Z], 2) * under);
}

static double	get_pt_on_cn(double *r, t_cn *cn, double *ori, double *center)
{
	double	under;
	double	a;
	double	b;
	double	c;
	double	o[3];

	under = pow(cos(atan(cn->radius / cn->height)), 2);
	sub_vect(o, ori, center);
	a = (pow(r[X] * cn->o_vect[X], 2) - pow(r[X], 2) * under
			+ 2 * r[X] * r[Y] * cn->o_vect[X] * cn->o_vect[Y]
			+ 2 * r[X] * r[Z] * cn->o_vect[X] * cn->o_vect[Z]
			+ pow(r[Y] * cn->o_vect[Y], 2) - pow(r[Y], 2) * under
			+ 2 * r[Y] * r[Z] * cn->o_vect[Y] * cn->o_vect[Z]
			+ pow(r[Z] * cn->o_vect[Z], 2) - pow(r[Z], 2) * under);
	b = get_cn_b(r, cn, o, under);
	c = get_cn_c(cn, o, under);
	if (signbit(pow(b, 2) - 4 * a * c))
		return (0);
	return ((b + sqrt(pow(b, 2) - 4 * a * c))
		/ (2 * a));
}

int	side_cn_shadow(double *ray, t_pt_info *pt_info, t_cn *cn, double r_size)
{
	double	t;
	double	pt[3];
	double	cur_vect[3];
	double	bottom[3];

	get_pt_on_line(bottom, cn->center, cn->o_vect, cn->height);
	t = get_pt_on_cn(ray, cn, pt_info->pt, bottom);
	if (t < 0.1 || (pt_info->pt[Z] != 1
			&& !signbit(pt_info->pt[Z] - ray[Z] * t)))
		return (0);
	get_pt_on_line(pt, pt_info->pt, ray, t);
	sub_vect(cur_vect, pt, bottom);
	if (!signbit(dot_product(cur_vect, cn->o_vect))
		|| !signbit(pow(vect_size(cur_vect), 2) - pow(cn->radius, 2)
			- pow(cn->height, 2)))
		return (0);
	if (!signbit(vect_size(cur_vect) - r_size))
		return (1);
	return (0);
}

int	intersect_cn(double *ray, t_pt_info *pt_info, t_cn *cn)
{
	double	t;
	double	pt[3];
	double	diff[3];
	double	origin[3];
	double	bottom[3];

	ft_bzero(origin, sizeof(double) * 3);
	get_pt_on_line(bottom, cn->center, cn->o_vect, cn->height);
	t = get_pt_on_cn(ray, cn, origin, bottom);
	if (t < 0.1 || (pt_info->pt[Z] != 1
			&& !signbit(pt_info->pt[Z] - ray[Z] * t)))
		return (0);
	get_pt_on_line(pt, origin, ray, t);
	sub_vect(diff, pt, bottom);
	if (!signbit(dot_product(diff, cn->o_vect))
		|| !signbit(pow(vect_size(diff), 2) - pow(cn->radius, 2)
			- pow(cn->height, 2)))
		return (0);
	vect_copy(pt_info->pt, pt);
	pt_info->type = CONE;
	pt_info->obj.cn = cn;
	copy_color(pt_info->color, cn->color);
	return (1);
}
