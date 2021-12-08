/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:09:19 by ghan              #+#    #+#             */
/*   Updated: 2021/12/08 15:28:17 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	meet_cy(double *ray, t_cy *cy, double min_angle)
// {
// 	double	d;

// 	while (min_angle < M_PI / 2)
// 	{
// 		d = pow(dot_product(ray, cy->center), 2) - (pow(vect_size(cy->center), 2)
// 				- pow((cy->diameter / 2) / sin(min_angle), 2));
// 		if (d >= 0)
// 			return (0);
// 		min_angle += M_PI / 180;
// 	}
// 	return (1);
// }

static double	get_pt_on_cy(double *ray, double *center, double *o_vect, double rad)
{
	double	a;
	double	b;
	double	c;

	a = pow(vect_size(ray), 2) - pow(ray[X] * o_vect[X], 2)
		- pow(ray[Y] * o_vect[Y], 2) - pow(ray[Z] * o_vect[Z], 2)
		- 2 * (ray[X] * ray[Y] *o_vect[X] *o_vect[Y]
			+ ray[X] * ray[Z] * o_vect[X] *o_vect[Z]
			+ ray[Y] * ray[Z] * o_vect[Y] * o_vect[Z]);
	b = - 2 * (dot_product(ray, center) - ray[X] *center[X] * pow(o_vect[X], 2)
			- ray[X] * center[Y] * o_vect[X] * o_vect[Y]
			- ray[X] *center[Z] * o_vect[X] * o_vect[Z]
			- ray[Y] * center[X] * o_vect[X] * o_vect[Y]
			- ray[Y] * center[Y] * pow(o_vect[Y], 2)
			- ray[Y] * center[Z] * o_vect[Y] * o_vect[Z]
			- ray[Z] * center[X] * o_vect[X] * o_vect[Z]
			- ray[Z] * center[Y] * o_vect[Y] * o_vect[Z]
			- ray[Z] * center[Z] * pow(o_vect[Z], 2));
	c = pow(vect_size(center), 2) - pow(rad, 2) - pow(center[X] * o_vect[X], 2)
		- pow(center[Y] * o_vect[Y], 2) - pow(center[Z] * o_vect[Z], 2)
		- 2 * (center[X] * center[Y] * o_vect[X] * o_vect[Y]
			+ center[X] * center[Z] * o_vect[X] * o_vect[Z]
			+ center[Y] * center[Z] * o_vect[Y] * o_vect[Z]);
	if (pow(b, 2) - 4 * a * c < 0)
		return (0);
	else if (pow(b, 2) - 4 * a * c < 0.2)
	{
		printf("abc\n");
		return (1);
	}
	return ((-1 * b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
}

void	intersect_cy(double *ray, t_pt_info *pt_info, t_cy *cy)
{
	double	t;
	// double	min_angle;
	double	pt[3];
	double	origin[3];
	double	diff[3];

	// min_angle = atan((cy->diameter / 2) / cy->height);
	// if (meet_cy(ray, cy, min_angle))
	// 	return ;
	fill_vect(origin, 0, 0, 0);
	t = get_pt_on_cy(ray, cy->center, cy->o_vect, cy->diameter / 2);
	if (t < 0.1)
		return ;
	if (pt_info->pt[Z] != 1 && pt_info->pt[Z] > ray[Z] * t)
		return ;
	get_pt_on_line(pt, NULL, ray, t);
	sub_vect(diff, pt, cy->center);
	if (pow(vect_size(diff), 2) - pow(cy->diameter / 2, 2) > pow(cy->height, 2) + 0.5)
		return ;
	if (pow(vect_size(diff), 2) - (pow(dot_product(diff, cy->o_vect), 2))
		> pow(cy->diameter / 2, 2) + 0.5)
		return ;
	fill_vect(pt_info->pt, pt[X], pt[Y], pt[Z]);
	pt_info->type = CYLINDER;
	pt_info->obj.cy = cy;
}
