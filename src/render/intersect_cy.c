/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:09:19 by ghan              #+#    #+#             */
/*   Updated: 2021/12/10 14:13:08 by ghan             ###   ########.fr       */
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

static double	get_cy_b(double *r, double *c, double *n, double *o)
{
	double	r_x_n_x;
	double	r_y_n_y;
	double	r_z_n_z;
	double	n_x_o_x;
	double	n_y_o_y;

	r_x_n_x = r[X] * n[X];
	r_y_n_y = r[Y] * n[Y];
	r_z_n_z = r[Z] * n[Z];
	n_x_o_x = n[X] * o[X];
	n_y_o_y = n[Y] * o[Y];
	return (2 * (r_x_n_x * c[X] * n[X] - r[X] * c[X] + r_x_n_x * c[Y] * n[Y]
			+ r_x_n_x * c[Z] * n[Z] - r_x_n_x * n_x_o_x - r_x_n_x * n_y_o_y
			- r_x_n_x * n[Z] * o[Z] + r[X] * o[X] + r_y_n_y * c[X] * n[X]
			+ r_y_n_y * c[Y] * n[Y] - r[Y] * c[Y] + r_y_n_y * c[Z] * n[Z]
			- r_y_n_y * n_x_o_x - r_y_n_y * n_y_o_y - r_y_n_y * n[Z] * o[Z]
			+ r[Y] * o[Y] + r_z_n_z * c[X] * n[X] + r_z_n_z * c[Y] * n[Y]
			+ r_z_n_z * c[Z] * n[Z] - r[Z] * c[Z] - r_z_n_z * n_x_o_x
			- r_z_n_z * n_y_o_y - r_z_n_z * n[Z] * o[Z] + r[Z] * o[Z]));
}

static double	get_cy_c(double *c, double *n, double *o, double rad)
{
	double	c_x_n_x;
	double	c_y_n_y;
	double	c_z_n_z;
	double	n_x_o_x;
	double	n_y_o_y;

	c_x_n_x = c[X] * n[X];
	c_y_n_y = c[Y] * n[Y];
	c_z_n_z = c[Z] * n[Z];
	n_x_o_x = n[X] * o[X];
	n_y_o_y = n[Y] * o[Y];
	return (pow(vect_size(c), 2) + pow(vect_size(o), 2)
		+ 2 * (c_x_n_x * n_x_o_x - c_x_n_x * c_y_n_y - c_x_n_x * c[Z] * n[Z]
			+ c_x_n_x * n_y_o_y + c_x_n_x * n[Z] * o[Z] - c[X] * o[X]
			- c_y_n_y * c[Z] * n[Z] + c_y_n_y * n_x_o_x + c_y_n_y * n_y_o_y
			+ c_y_n_y * n[Z] * o[Z] - c[Y] * o[Y] + c_z_n_z * n_x_o_x
			+ c_z_n_z * n_y_o_y + c_z_n_z * n[Z] * o[Z] - c[Z] * o[Z]
			- n[X] * n[Y] * o[X] * o[Y] - n[X] * n[Z] * o[X] * o[Z]
			- n[Y] * n[Z] * o[Y] * o[Z])
		- pow(c_y_n_y, 2) - pow(c_z_n_z, 2) - pow(n_x_o_x, 2) - pow(n_y_o_y, 2)
		- pow(n[Z] * o[Z], 2) - pow(rad, 2) - pow(c_x_n_x, 2));
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
	b = get_cy_b(r, cy->center, cy->o_vect, o);
	c = get_cy_c(cy->center, cy->o_vect, o, rad);
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
