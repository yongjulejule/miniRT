/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_pl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:08:20 by ghan              #+#    #+#             */
/*   Updated: 2021/12/19 20:58:19 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	meet_pl(double *ray, double *o_vect)
{
	return (dot_product(ray, o_vect));
}

int	intersect_pl(double *ray, t_pt_info *pt_info, t_pl *pl)
{
	double	t;

	if (fpclassify(meet_pl(ray, pl->o_vect)) == FP_ZERO)
		return (0);
	t = (dot_product(pl->center, pl->o_vect)) / dot_product(ray, pl->o_vect);
	if (t < 0.1 || (pt_info->pt[Z] != 1
			&& !signbit(pt_info->pt[Z] - ray[Z] * t)))
		return (0);
	get_pt_on_line(pt_info->pt, NULL, ray, t);
	pt_info->type = PLANE;
	pt_info->obj.pl = pl;
	copy_color(pt_info->color, pl->color);
	return (1);
}

int	pl_shadow(double *ray, t_pt_info *pt_info, t_pl *pl, double r_size)
{
	double	t;
	double	d;
	double	pt[3];
	double	int_pt[3];

	if (!meet_pl(ray, pl->o_vect))
		return (0);
	t = (dot_product(pl->center, pl->o_vect) - dot_product(pt_info->pt,
				pl->o_vect)) / dot_product(ray, pl->o_vect);
	get_pt_on_line(pt, pt_info->pt, ray, t);
	sub_vect(int_pt, pt, pt_info->pt);
	d = vect_size(int_pt);
	if (signbit(d - r_size + 0.1) && t > 0.1)
		return (1);
	return (0);
}
