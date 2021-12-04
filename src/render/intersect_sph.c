/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:07:42 by ghan              #+#    #+#             */
/*   Updated: 2021/12/04 14:32:43y yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	meet_sph(double *o_vect, double *origin, t_sph *sph)
{
	double	diff[3];

	if (!origin)
	{
		return (pow(dot_product(o_vect, sph->center), 2)
			- (dot_product(sph->center, sph->center)
				- pow(sph->diameter / 2, 2)));
	}
	sub_vect(diff, origin, sph->center);
	return (pow(dot_product(o_vect, diff), 2)
		- (pow(vect_size(diff), 2) - pow(sph->diameter / 2, 2)));
}

void	intersect_sph(double *o_vect, t_pt_info *pt_info, t_sph *sph)
{
	double	d;
	double	t;

	d = meet_sph(o_vect, NULL, sph);
	if (d < 0)
		return ;
	t = (dot_product(o_vect, sph->center) - sqrt(d));
	if (pt_info->pt[Z] == 1 || pt_info->pt[Z] <= o_vect[Z] * t)
		pt_info->pt[Z] = o_vect[Z] * t;
	else
		return ;
	pt_info->pt[X] = o_vect[X] * t;
	pt_info->pt[Y] = o_vect[Y] * t;
	pt_info->type = SPHERE;
	pt_info->obj.sph = sph;
	return ;
}
