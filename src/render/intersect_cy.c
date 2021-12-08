/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:09:19 by ghan              #+#    #+#             */
/*   Updated: 2021/12/08 18:22:48 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void intersect_circle(double *ray, t_pt_info *pt_i, t_cy *cy, double *cam_o_v)
{
	double		diff[3];
	t_pl		pl;
	t_pt_info	local;

	local.pt[Z] = pt_i->pt[Z];
	if (dot_product(cy->o_vect, cam_o_v) > 0)
		fill_vect(pl.center, cy->center[X], cy->center[Y], cy->center[Z]);
	else
		fill_vect(pl.center, cy->center[X] + cy->o_vect[X] * cy->height
		, cy->center[Y] + cy->o_vect[Y] * cy->height
		, cy->center[Z] + cy->o_vect[X] * cy->height);
	if (dot_product(cy->o_vect, cam_o_v) > 0)
		fill_vect(pl.o_vect, cy->o_vect[X], cy->o_vect[Y], cy->o_vect[Z]);
	else
		fill_vect(pl.o_vect, -1 * cy->o_vect[X], -1 * cy->o_vect[Y]
			, -1 * cy->o_vect[Z]);

	intersect_pl(ray, &local, &pl);
	if (local.pt[Z] == 1 || local.pt[Z] == pt_i->pt[Z])
		return ;
	sub_vect(diff, pl.center, local.pt);
	if (vect_size(diff) > cy->radius)
		return ;
	fill_vect(pt_i->pt, local.pt[X], local.pt[Y], local.pt[Z]);
	pt_i->type = CY_CIRCLE;
	fill_vect(pt_i->c_o_vect, pl.o_vect[X], pl.o_vect[Y], pl.o_vect[Z]);
}

static double	get_pt_on_cy(double *r, double *o, double *n, double rad)
{
	double	a;
	double	b;
	double	c;

	a = pow(vect_size(r), 2) - pow(r[X] * n[X], 2)
		- pow(r[Y] * n[Y], 2) - pow(r[Z] * n[Z], 2)
		- 2 * (r[X] * r[Y] *n[X] *n[Y] + r[X] * r[Z] * n[X] *n[Z]
			+ r[Y] * r[Z] * n[Y] * n[Z]);
	b = - 2 * (dot_product(r, o) - r[X] * o[X] * pow(n[X], 2)
			- r[X] * o[Y] * n[X] * n[Y] - r[X] *o[Z] * n[X] * n[Z]
			- r[Y] * o[X] * n[X] * n[Y] - r[Y] * o[Y] * pow(n[Y], 2)
			- r[Y] * o[Z] * n[Y] * n[Z] - r[Z] * o[X] * n[X] * n[Z]
			- r[Z] * o[Y] * n[Y] * n[Z] - r[Z] * o[Z] * pow(n[Z], 2));
	c = pow(vect_size(o), 2) - pow(rad, 2) - pow(o[X] * n[X], 2)
		- pow(o[Y] * n[Y], 2) - pow(o[Z] * n[Z], 2)
		- 2 * (o[X] * o[Y] * n[X] * n[Y] + o[X] * o[Z] * n[X] * n[Z]
			+ o[Y] * o[Z] * n[Y] * n[Z]);
	if (pow(b, 2) - 4 * a * c < 0)
		return (0);
	return ((-1 * b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
}

int	intersect_cy(double *ray, t_pt_info *pt_info, t_cy *cy)
{
	double	t;
	double	pt[3];
	double	origin[3];
	double	diff[3];

	fill_vect(origin, 0, 0, 0);
	t = get_pt_on_cy(ray, cy->center, cy->o_vect, cy->radius);
	if (t < 0.1 || (pt_info->pt[Z] != 1 && pt_info->pt[Z] > ray[Z] * t))
		return (0);
	get_pt_on_line(pt, NULL, ray, t);
	sub_vect(diff, pt, cy->center);
	if (dot_product(diff, cy->o_vect) < 0
		|| pow(vect_size(diff), 2) - pow(cy->radius, 2)
			> pow(cy->height, 2) - 0.5)
		return (0);
	if (pow(vect_size(diff), 2) - (pow(dot_product(diff, cy->o_vect), 2))
		> pow(cy->radius, 2) + 0.5)
		return (0);
	fill_vect(pt_info->pt, pt[X], pt[Y], pt[Z]);
	pt_info->type = CYLINDER;
	pt_info->obj.cy = cy;
	return (1);
}
