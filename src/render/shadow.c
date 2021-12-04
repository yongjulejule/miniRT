/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 01:36:32 by ghan              #+#    #+#             */
/*   Updated: 2021/12/05 01:42:18 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_hidden_by_pl(t_pl *pl, double *ray, double *lp, double *cur_pt)
{
	t_pt_info	intersect;
	double		lp_pl[3];
	double		lp_pt[3];

	if (intersect_pl(ray, &intersect, pl))
	{
		sub_vect(lp_pl, intersect.pt, lp);
		sub_vect(lp_pt, cur_pt, lp);
		if (vect_size(lp_pl) > vect_size(lp_pt))
			return (1);
	}
	return (0);
}

double	get_shadow(t_rt *rt, t_pt_info *pt_info)
{
	int			shaded;
	double		ray[3];
	t_obj_lst	*cur;

	shaded = 0;
	sub_vect(ray, rt->spec->light.lp, pt_info->pt);
	normalize_vect(ray);
	cur = rt->spec->obj_lst->next;
	while (cur)
	{
		shaded = 0;
		if (cur->type == SPHERE && cur->obj.sph != pt_info->obj.sph)
			shaded = (meet_sph(ray, pt_info->pt, cur->obj.sph) >= 0);
		else if (cur->type == PLANE && cur->obj.pl != pt_info->obj.pl
			&& is_hidden_by_pl(cur->obj.pl, ray,
				rt->spec->light.lp, pt_info->pt))
			shaded = (meet_pl(ray, cur->obj.pl) != 0);
		// TODO - SHADOW WHEN CYLINDER IS MET
		// else if (cur->type == CYLINDER)
		// 	intersect_cy(ray, &pt_info, cur->obj.cy);
		if (shaded == 1)
			return (SHADED);
		cur = cur->next;
	}
	return (NOT_SHADED);
}
