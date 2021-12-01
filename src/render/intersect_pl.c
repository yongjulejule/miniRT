/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_pl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:08:20 by ghan              #+#    #+#             */
/*   Updated: 2021/12/01 17:08:05 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	meet_pl(double *o_vect, t_pl *pl)
{
	return (dot_product(o_vect, pl->o_vect));
}

void	intersect_pl(double *o_vect, t_pt_info *pt_info, t_pl *pl)
{
	double	t;

	if (!meet_pl(o_vect, pl))
		return ;
	t = (dot_product(pl->center, pl->o_vect) - dot_product(o_vect, pl->o_vect))
		/ dot_product(o_vect, pl->o_vect);
	if (pt_info->pt[Z] > o_vect[Z] * t)
		pt_info->pt[Z] = o_vect[Z] + o_vect[Z] * t;
	else
		return ;
	pt_info->pt[X] = o_vect[X] + o_vect[X] * t;
	pt_info->pt[Y] = o_vect[Y] + o_vect[Y] * t;
	pt_info->type = PLANE;
	pt_info->obj.pl = pl;
}
