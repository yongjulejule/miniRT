/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:07:42 by ghan              #+#    #+#             */
/*   Updated: 2021/12/02 14:29:51 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	meet_sph(double *o_vect, t_sph *sph)
{
	return (pow(dot_product(o_vect, sph->center), 2)
		- (dot_product(sph->center, sph->center)
			- pow(sph->diameter / 2, 2)));
}

/* NOTE : Can be wrong */
void	intersect_sph(double *o_vect, t_pt_info *pt_info, t_sph *sph)
{
	double	d;
	double	t;

	d = meet_sph(o_vect, sph);
	if (d < 0)
		return ;
	t = (dot_product(o_vect, sph->center) - sqrt(d)) / 2;
	if (pt_info->pt[Z] > o_vect[Z] * t) // NOTE - WRONG
		pt_info->pt[Z] = o_vect[Z] * t;
	else
		return ;
	pt_info->pt[X] = o_vect[X] * t;
	pt_info->pt[Y] = o_vect[Y] * t;
	pt_info->type = SPHERE;
	pt_info->obj.sph = sph;
}
