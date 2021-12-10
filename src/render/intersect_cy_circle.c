/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy_circle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:40:04 by ghan              #+#    #+#             */
/*   Updated: 2021/12/10 18:00:31 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	which_circle(t_cy *cy, double *origin)
{
	double	diff_base[3];
	double	diff_top[3];
	double	t_center[3];

	sub_vect(diff_base, cy->center, origin);
	get_pt_on_line(t_center, cy->center, cy->o_vect, cy->height);
	sub_vect(diff_top, t_center, origin);
	return (vect_size(diff_base) < vect_size(diff_top));
}

int	circle_shadow(double *ray, t_pt_info *pt_i, t_cy *cy, double r_size)
{
	double	t;
	double	center[3];
	double	pt_on_cir[3];
	double	pl_to_cir[3];
	double	cir_to_cent[3];

	if (which_circle(cy, pt_i->pt))
		vect_copy(center, cy->center);
	else
		get_pt_on_line(center, cy->center, cy->o_vect, cy->height);
	if (!meet_pl(ray, cy->o_vect))
		return (0);
	t = (dot_product(center, cy->o_vect) - dot_product(pt_i->pt,
				cy->o_vect)) / dot_product(ray, cy->o_vect);
	get_pt_on_line(pt_on_cir, pt_i->pt, ray, t);
	sub_vect(pl_to_cir, pt_on_cir, pt_i->pt);
	sub_vect(cir_to_cent, pt_on_cir, center);
	if (t > 0 && vect_size(pl_to_cir) < r_size - 0.5
		&& vect_size(cir_to_cent) <= cy->radius + 0.1)
		return (1);
	return (0);
}

void	intersect_circle(double *ray, t_pt_info *pt_i, t_cy *cy)
{
	double		pt_to_center[3];
	t_pl		pl;
	t_pt_info	pt_on_pl;

	pt_on_pl.pt[Z] = pt_i->pt[Z];
	vect_copy(pl.center, cy->circle_center);
	vect_copy(pl.o_vect, cy->circle_o_v);
	if (!intersect_pl(ray, &pt_on_pl, &pl))
		return ;
	sub_vect(pt_to_center, pt_on_pl.pt, pl.center);
	if (vect_size(pt_to_center) > cy->radius + 0.1)
		return ;
	vect_copy(pt_i->pt, pt_on_pl.pt);
	pt_i->type = CY_CIRCLE;
	pt_i->obj.cy = cy;
	vect_copy(pt_i->obj.cy->circle_o_v, pl.o_vect);
}
