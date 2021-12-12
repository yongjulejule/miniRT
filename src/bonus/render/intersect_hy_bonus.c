/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_hy_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:19:16 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/12 19:39:51 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static double	get_pt_on_hy(double *r, t_hy *hy, double *o, double rad)
{
	double	a;
	double	b;
	double	c;
	double	diff[3];

	sub_vect(diff, o, hy->center);
	a = ((-2 * pow(r[X] * hy->o_vect[X], 2)
				- 4 * r[X] * r[Y] * hy->o_vect[X] * hy->o_vect[Y]
				- 4 * r[X] * r[Z] * hy->o_vect[X] * hy->o_vect[Z]
				- 2 * pow(r[Y] * hy->o_vect[Y], 2)
				- 4 * r[Y] * r[Z] * hy->o_vect[Y]
				* hy->o_vect[Z] - 2 * pow(r[Z] * hy->o_vect[Z], 2) + 1));
	b = (-4 * diff[X] * r[X] * pow(hy->o_vect[X], 2) + 2 * diff[X] * r[X] - 4
			* diff[X] * r[Y] * hy->o_vect[X] * hy->o_vect[Y]
			- 4 * diff[X] * r[Z] * hy->o_vect[X] * hy->o_vect[Z]
			- 4 * diff[Y] * r[X] * hy->o_vect[X] * hy->o_vect[Y] - 4 * diff[Y]
			* r[Y] * pow(hy->o_vect[Y], 2) + 2 * diff[Y] * r[Y]
			- 4 * diff[Y] * r[Z] * hy->o_vect[Y] * hy->o_vect[Z] - 4 * diff[Z]
			* r[X] * hy->o_vect[X] * hy->o_vect[Z] - 4 * diff[Z] * r[Y] *
			hy->o_vect[Y] * hy->o_vect[Z] - 4 * diff[Z] * r[Z]
			* pow(hy->o_vect[Z], 2) + 2 * diff[Z] * r[Z]);
	c = (-2 * pow(diff[X] * hy->o_vect[X], 2) + pow(diff[X], 2) - 4 * diff[X]
			* diff[Y] * hy->o_vect[X] * hy->o_vect[Y] - 4 * diff[X] * diff[Z]
			* hy->o_vect[X] * hy->o_vect[Z] - 2 * pow(diff[Y]
				* hy->o_vect[Y], 2) + pow(diff[Y], 2) - 4 * diff[Y] * diff[Z]
			* hy->o_vect[Y] * hy->o_vect[Z] - 2 * pow(diff[Z]
				* hy->o_vect[Z], 2) + pow(diff[Z], 2) - pow(rad, 2));
	if (pow(b, 2) - 4 * a * c < 0)
		return (0);
	return ((-1 * b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
}

static double	get_pt_on_hy_far(double *r, t_hy *hy, double *o, double rad)
{
	double	a;
	double	b;
	double	c;
	double	diff[3];

	sub_vect(diff, o, hy->center);
	a = ((-2 * pow(r[X] * hy->o_vect[X], 2)
				- 4 * r[X] * r[Y] * hy->o_vect[X] * hy->o_vect[Y]
				- 4 * r[X] * r[Z] * hy->o_vect[X] * hy->o_vect[Z]
				- 2 * pow(r[Y] * hy->o_vect[Y], 2)
				- 4 * r[Y] * r[Z] * hy->o_vect[Y]
				* hy->o_vect[Z] - 2 * pow(r[Z] * hy->o_vect[Z], 2) + 1));
	b = (-4 * diff[X] * r[X] * pow(hy->o_vect[X], 2) + 2 * diff[X] * r[X] - 4
			* diff[X] * r[Y] * hy->o_vect[X] * hy->o_vect[Y]
			- 4 * diff[X] * r[Z] * hy->o_vect[X] * hy->o_vect[Z]
			- 4 * diff[Y] * r[X] * hy->o_vect[X] * hy->o_vect[Y] - 4 * diff[Y]
			* r[Y] * pow(hy->o_vect[Y], 2) + 2 * diff[Y] * r[Y]
			- 4 * diff[Y] * r[Z] * hy->o_vect[Y] * hy->o_vect[Z] - 4 * diff[Z]
			* r[X] * hy->o_vect[X] * hy->o_vect[Z] - 4 * diff[Z] * r[Y] *
			hy->o_vect[Y] * hy->o_vect[Z] - 4 * diff[Z] * r[Z]
			* pow(hy->o_vect[Z], 2) + 2 * diff[Z] * r[Z]);
	c = (-2 * pow(diff[X] * hy->o_vect[X], 2) + pow(diff[X], 2) - 4 * diff[X]
			* diff[Y] * hy->o_vect[X] * hy->o_vect[Y] - 4 * diff[X] * diff[Z]
			* hy->o_vect[X] * hy->o_vect[Z] - 2 * pow(diff[Y]
				* hy->o_vect[Y], 2) + pow(diff[Y], 2) - 4 * diff[Y] * diff[Z]
			* hy->o_vect[Y] * hy->o_vect[Z] - 2 * pow(diff[Z]
				* hy->o_vect[Z], 2) + pow(diff[Z], 2) - pow(rad, 2));
	if (pow(b, 2) - 4 * a * c < 0)
		return (0);
	return ((-1 * b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
}

int	hy_shadow(double *ray, t_pt_info *pt_info, t_hy *hy, double r_size)
{
	double	t;
	double	pt[3];
	double	diff[3];
	double	cur_vect[3];

	t = get_pt_on_hy(ray, hy, pt_info->pt, hy->radius);
	if (t < 0.1 || (pt_info->pt[Z] != 1 && pt_info->pt[Z] > ray[Z] * t))
		return (0);
	get_pt_on_line(pt, pt_info->pt, ray, t);
	sub_vect(diff, pt, hy->center);
	if (pow(vect_size(diff), 2) - pow(hy->radius, 2) > pow(hy->height, 2) - 0.5)
	{
		t = get_pt_on_hy_far(ray, hy, pt_info->pt, hy->radius);
		if (t < 0.1 || (pt_info->pt[Z] != 1 && pt_info->pt[Z] > ray[Z] * t))
			return (0);
		get_pt_on_line(pt, pt_info->pt, ray, t);
		sub_vect(diff, pt, hy->center);
		if (pow(vect_size(diff), 2) - pow(hy->radius, 2) > pow(hy->height, 2) - 0.5)
			return (0);
	}
	sub_vect(cur_vect, pt, pt_info->pt);
	if (vect_size(cur_vect) < r_size < 0.5)
		return (1);
	return (0);
}


void	intersect_hy(double *ray, t_pt_info *pt_info, t_hy *hy)
{
	double	t;
	double	pt[3];
	double	diff[3];
	double	origin[3];

	ft_bzero(origin, sizeof(double) * 3);
	t = get_pt_on_hy(ray, hy, origin, hy->radius);
	if (t < 0.1 || (pt_info->pt[Z] != 1 && pt_info->pt[Z] > ray[Z] * t))
		return ;
	get_pt_on_line(pt, origin, ray, t);
	sub_vect(diff, pt, hy->center);
	if (pow(vect_size(diff), 2) - pow(hy->radius, 2) > pow(hy->height, 2) - 0.5)
	{
		t = get_pt_on_hy_far(ray, hy, origin, hy->radius);
		if (t < 0.1 || (pt_info->pt[Z] != 1 && pt_info->pt[Z] > ray[Z] * t))
			return ;
		get_pt_on_line(pt, origin, ray, t);
		sub_vect(diff, pt, hy->center);
		if (pow(vect_size(diff), 2) - pow(hy->radius, 2) > pow(hy->height, 2) - 0.5)
			return ;
	}
	vect_copy(pt_info->pt, pt);
	pt_info->type = HYPERBOLOID;
	pt_info->obj.hy = hy;
	return ;
}
