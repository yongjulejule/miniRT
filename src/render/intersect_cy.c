/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:09:19 by ghan              #+#    #+#             */
/*   Updated: 2021/12/09 19:31:17 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_circle(double *ray, t_pt_info *pt_i,
			t_cy *cy, double *cam_o_v)
{
	double		center_to_cir[3];
	t_pl		pl;
	t_pt_info	pt_on_pl;

	pt_on_pl.pt[Z] = pt_i->pt[Z];
	if (dot_product(cy->o_vect, cam_o_v) > 0)
		vect_copy(pl.center, cy->center);
	else
		get_pt_on_line(pl.center, cy->center, cy->o_vect, cy->height);
	if (dot_product(cy->o_vect, cam_o_v) < 0)
		vect_copy(pl.o_vect, cy->o_vect);
	else
		fill_vect(pl.o_vect, -1 * cy->o_vect[X],
			-1 * cy->o_vect[Y], -1 * cy->o_vect[Z]);
	if (!intersect_pl(ray, &pt_on_pl, &pl))
		return ;
	sub_vect(center_to_cir, pt_on_pl.pt, pl.center);
	if (vect_size(center_to_cir) > cy->radius)
		return ;
	vect_copy(pt_i->pt, pt_on_pl.pt);
	pt_i->type = CY_CIRCLE;
	vect_copy(pt_i->c_o_vect, pl.o_vect);
	pt_i->obj.cy = cy;
}

static double	get_cy_b(double *r, t_cy *cy, double *o)
{
	return (2 * (r[X] * cy->center[X] * pow(cy->o_vect[X], 2)
			- r[X] * cy->center[X]
			+ r[X] * cy->center[Y] * cy->o_vect[X] * cy->o_vect[Y]
			+ r[X] * cy->center[Z] * cy->o_vect[X] * cy->o_vect[Z]
			- r[X] * pow(cy->o_vect[X], 2) * o[X]
			- r[X] * cy->o_vect[X] * cy->o_vect[Y] * o[Y]
			- r[X] * cy->o_vect[X] * cy->o_vect[Z] * o[Z]
			+ r[X] * o[X] + r[Y] * cy->center[X]
			* cy->o_vect[X] * cy->o_vect[Y]
			+ r[Y] * cy->center[Y]
			* pow(cy->o_vect[Y], 2) - r[Y] * cy->center[Y]
			+ r[Y] * cy->center[Z] * cy->o_vect[Y] * cy->o_vect[Z]
			- r[Y] * cy->o_vect[X] * cy->o_vect[Y] * o[X]
			- r[Y] * pow(cy->o_vect[Y], 2) * o[Y]
			- r[Y] * cy->o_vect[Y] * cy->o_vect[Z] * o[Z] + r[Y] * o[Y]
			+ r[Z] * cy->center[X] * cy->o_vect[X] * cy->o_vect[Z]
			+ r[Z] * cy->center[Y] * cy->o_vect[Y] * cy->o_vect[Z]
			+ r[Z] * cy->center[Z]
			* pow(cy->o_vect[Z], 2) - r[Z] * cy->center[Z]
			- r[Z] * cy->o_vect[X] * cy->o_vect[Z] * o[X]
			- r[Z] * cy->o_vect[Y] * cy->o_vect[Z] * o[Y]
			- r[Z] * pow(cy->o_vect[Z], 2) * o[Z] + r[Z] * o[Z]));
}

static double	get_cy_c(t_cy *cy, double *o, double rad)
{
	return (pow(vect_size(cy->center), 2) + pow(vect_size(o), 2)
		+ 2 * (cy->center[X] * pow(cy->o_vect[X], 2) * o[X]
			- cy->center[X] * cy->center[Y] * cy->o_vect[X] * cy->o_vect[Y]
			- cy->center[X] * cy->center[Z] * cy->o_vect[X] * cy->o_vect[Z]
			+ cy->center[X] * cy->o_vect[X] * cy->o_vect[Y] * o[Y]
			+ cy->center[X] * cy->o_vect[X] * cy->o_vect[Z] * o[Z]
			- cy->center[X] * o[X]
			- cy->center[Y] * cy->center[Z] * cy->o_vect[Y] * cy->o_vect[Z]
			+ cy->center[Y] * cy->o_vect[X] * cy->o_vect[Y] * o[X]
			+ cy->center[Y] * pow(cy->o_vect[Y], 2) * o[Y]
			+ cy->center[Y] * cy->o_vect[Y] * cy->o_vect[Z] * o[Z]
			- cy->center[Y] * o[Y]
			+ cy->center[Z] * cy->o_vect[X] * cy->o_vect[Z] * o[X]
			+ cy->center[Z] * cy->o_vect[Y] * cy->o_vect[Z] * o[Y]
			+ cy->center[Z] * pow(cy->o_vect[Z], 2) * o[Z]
			- cy->center[Z] * o[Z]
			- cy->o_vect[X] * cy->o_vect[Y] * o[X] * o[Y]
			- cy->o_vect[X] * cy->o_vect[Z] * o[X] * o[Z]
			- cy->o_vect[Y] * cy->o_vect[Z] * o[Y] * o[Z])
		- pow(cy->center[Y] * cy->o_vect[Y], 2)
		- pow(cy->center[Z] * cy->o_vect[Z], 2)
		- pow(cy->o_vect[X] * o[X], 2) - pow(cy->o_vect[Y] * o[Y], 2)
		- pow(cy->o_vect[Z] * o[Z], 2) - pow(rad, 2)
		- pow(cy->center[X] * cy->o_vect[X], 2));
}

static double	get_pt_on_cy(double *r, t_cy *cy, double *o, double rad)
{
	double	a;
	double	b;
	double	c;

	a = pow(vect_size(r), 2) - 2 * (r[X] * r[Y] * cy->o_vect[X] * cy->o_vect[Y]
			+ r[X] * r[Z] * cy->o_vect[X] * cy->o_vect[Z]
			+ r[Y] * r[Z] * cy->o_vect[Y] * cy->o_vect[Z])
		- pow(r[X] * cy->o_vect[X], 2) - pow(r[Y] * cy->o_vect[Y], 2)
		- pow(r[Z] * cy->o_vect[Z], 2);
	b = get_cy_b(r, cy, o);
	c = get_cy_c(cy, o, rad);
	if (pow(b, 2) - 4 * a * c < 0)
		return (0);
	return ((-1 * b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
}

int	intersect_cy(double *ray, t_pt_info *pt_info, t_cy *cy, double *shadow)
{
	double	t;
	double	pt[3];
	double	diff[3];
	double	origin[3];

	ft_bzero(origin, sizeof(double) * 3);
	if (shadow)
		vect_copy(origin, shadow);
	t = get_pt_on_cy(ray, cy, origin, cy->radius);
	if (t < 0.1 || (pt_info->pt[Z] != 1 && pt_info->pt[Z] > ray[Z] * t))
		return (0);
	get_pt_on_line(pt, origin, ray, t);
	sub_vect(diff, pt, cy->center);
	if (dot_product(diff, cy->o_vect) < 0
		|| pow(vect_size(diff), 2) - pow(cy->radius, 2)
		> pow(cy->height, 2) - 0.5)
		return (0);
	if (shadow)
		return (1);
	vect_copy(pt_info->pt, pt);
	pt_info->type = CYLINDER;
	pt_info->obj.cy = cy;
	return (1);
}
