/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cn_circle_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:55:54 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/13 22:38:56 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	circle_cn_shadow(double *ray, t_pt_info *pt_i, t_cn *cn, double r_size)
{
	double	t;
	double	pt_on_cir[3];
	double	center[3];
	double	cir_to_cent[3];
	double	cur_to_cir[3];

	vect_copy(center, cn->center);
	if (!meet_pl(ray, cn->o_vect))
		return (0);
	t = (dot_product(center, cn->o_vect) - dot_product(pt_i->pt,
				cn->o_vect)) / dot_product(ray, cn->o_vect);
	get_pt_on_line(pt_on_cir, pt_i->pt, ray, t);
	sub_vect(cur_to_cir, pt_on_cir, pt_i->pt);
	sub_vect(cir_to_cent, pt_on_cir, center);
	if (t > 0 && vect_size(cur_to_cir) < r_size - 0.5
		&& vect_size(cir_to_cent) <= cn->radius + 0.1)
		return (1);
	return (0);
}

void	intersect_cn_circle(double *ray, t_pt_info *pt_i, t_cn *cn)
{
	double		pt_to_center[3];
	t_pl		pl;
	t_pt_info	pt_on_pl;

	pt_on_pl.pt[Z] = pt_i->pt[Z];
	vect_copy(pl.center, cn->center);
	get_pt_on_line(pl.o_vect, NULL, cn->o_vect, -1);
	if (!intersect_pl(ray, &pt_on_pl, &pl))
		return ;
	sub_vect(pt_to_center, pt_on_pl.pt, pl.center);
	if (vect_size(pt_to_center) > cn->radius + 0.1)
		return ;
	vect_copy(pt_i->pt, pt_on_pl.pt);
	pt_i->type = CN_CIRCLE;
	pt_i->obj.cn = cn;
	vect_copy(pt_i->obj.cn->circle_o_v, pl.o_vect);
}
