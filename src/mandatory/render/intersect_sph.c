/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:07:42 by ghan              #+#    #+#             */
/*   Updated: 2021/12/19 21:06:53 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	meet_sph(double *ray, double *origin, t_sph *sph, double r_size)
{
	double	diff[3];
	double	int_pt[3];
	double	d;
	double	t;

	if (!origin)
	{
		return (pow(dot_product(ray, sph->center), 2)
			- (dot_product(sph->center, sph->center)
				- pow(sph->radius, 2)));
	}
	sub_vect(diff, origin, sph->center);
	d = (pow(dot_product(ray, diff), 2)
			- (pow(vect_size(diff), 2) - pow(sph->radius, 2)));
	if (signbit(d))
		return (-1);
	t = -1 * dot_product(diff, ray) - sqrt(d);
	get_pt_on_line(int_pt, origin, ray, t);
	sub_vect(diff, int_pt, origin);
	if (signbit(vect_size(diff) - r_size + 0.1) && t > 0.1)
		return (1);
	return (-1);
}

void	intersect_sph(double *ray, t_pt_info *pt_info, t_sph *sph)
{
	double	d;
	double	t;

	d = meet_sph(ray, NULL, sph, 0);
	if (d < 0)
		return ;
	t = dot_product(ray, sph->center) - sqrt(d);
	if (t < 0.1)
		return ;
	if (pt_info->pt[Z] != 1 && !signbit(pt_info->pt[Z] - ray[Z] * t))
		return ;
	get_pt_on_line(pt_info->pt, NULL, ray, t);
	pt_info->type = SPHERE;
	pt_info->obj.sph = sph;
	copy_color(pt_info->color, sph->color);
}
