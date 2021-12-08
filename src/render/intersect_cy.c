/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:09:19 by ghan              #+#    #+#             */
/*   Updated: 2021/12/08 13:16:37 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	meet_cy(double *ray, t_cy *cy, double min_angle)
{
	double	d;

	while (min_angle < M_PI / 2)
	{
		d = pow(dot_product(ray, cy->center), 2) - (pow(vect_size(cy->center), 2)
				- pow((cy->diameter / 2) / sin(min_angle), 2));
		if (d >= 0)
			return (0);
		min_angle += M_PI / 180;
	}
	return (1);
}

static double	get_pt_on_cy(double *ray, t_cy *cy/* , double *origin */)
{
	double	a;
	double	b;
	double	c;

	a = 2 * (pow(cy->o_vect[Z] * ray[Y], 2) + pow(cy->o_vect[X] * ray[Z], 2) 
			+ pow(cy->o_vect[Y] * ray[X], 2) - cy->o_vect[Z] * cy->o_vect[Y]
			* ray[Y] * ray[Z] - cy->o_vect[X] * cy->o_vect[Z] * ray[Z] * ray[X]
			- cy->o_vect[Y] * cy->o_vect[X] * ray[X] * ray[Y]);
	b = -2 * (2 * (pow(cy->o_vect[Z], 2) * ray[Y] * cy->center[Y]
				+ pow(cy->o_vect[X], 2) * ray[Z] * cy->center[Z]
				+ pow(cy->o_vect[Y], 2) * ray[X] * cy->center[X])
			-1 * (cy->o_vect[Z] * cy->o_vect[Y] * (ray[Y] * cy->center[Z]
					+ ray[Z] * cy->center[Y]) + cy->o_vect[X] * cy->o_vect[Z]
				* (ray[Z] * cy->center[X] + ray[X] * cy->center[Z])
				+ cy->o_vect[Y] * cy->o_vect[X]
				* (ray[X] * cy->center[Y] + ray[Y] * cy->center[X])));
	c = 2 * (pow(cy->o_vect[Z] * cy->center[Y], 2)
			+ pow(cy->o_vect[X] * cy->center[Z], 2)
			+ pow(cy->o_vect[Y] * cy->center[X], 2)
			- cy->o_vect[Z] * cy->o_vect[Y] * cy->center[Y] * cy->center[Z]
			- cy->o_vect[X] * cy->o_vect[Z] * cy->center[Z] * cy->center[X]
			- cy->o_vect[Y] * cy->o_vect[X] * cy->center[X] * cy->center[Y])
		- pow(cy->diameter / 2, 2);
	if (pow(b, 2) - 4 * a * c < 0)
		return (0);
	return ((-1 * b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
}

void	intersect_cy(double *ray, t_pt_info *pt_info, t_cy *cy)
{
	double	t;
	double	min_angle;
	double	pt[3];
	double	origin[3];
	double	diff[3];

	min_angle = atan((cy->diameter / 2) / cy->height);
	if (meet_cy(ray, cy, min_angle))
		return ;
	fill_vect(origin, 0, 0, 0);
	t = get_pt_on_cy(ray, cy/* , origin */);
	if (t < 0.1)
		return ;
	if (pt_info->pt[Z] != 1 && pt_info->pt[Z] > ray[Z] * t)
		return ;
	get_pt_on_line(pt, NULL, ray, t);
	sub_vect(diff, pt, cy->center);
	// if (pow(vect_size(diff), 2) - (pow(dot_product(diff, cy->o_vect), 2))
	// 	> pow(cy->diameter / 2, 2) + 0.5)
	// 	return ;
	fill_vect(pt_info->pt, pt[X], pt[Y], pt[Z]);
	pt_info->type = CYLINDER;
	pt_info->obj.cy = cy;
}
