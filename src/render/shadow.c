/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 01:36:32 by ghan              #+#    #+#             */
/*   Updated: 2021/12/09 12:26:08 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_shadow(t_rt *rt, t_pt_info *pt_info)
{
	int			shaded;
	double		ray[3];
	double		r_size;
	t_obj_lst	*cur;

	shaded = 0;
	sub_vect(ray, rt->spec->light.lp, pt_info->pt);
	r_size = vect_size(ray);
	normalize_vect(ray);
	cur = rt->spec->obj_lst->next;
	while (cur)
	{
		shaded = 0;
		if (cur->type == SPHERE && cur->obj.sph != pt_info->obj.sph)
			shaded = (meet_sph(ray, pt_info->pt, cur->obj.sph, r_size) >= 0);
		else if (cur->type == PLANE && cur->obj.pl != pt_info->obj.pl)
			shaded = pl_shadow(ray, pt_info, cur->obj.pl, r_size);
		else if (cur->type == CYLINDER && cur->obj.cy != pt_info->obj.cy)
			shaded = intersect_cy(ray, pt_info, cur->obj.cy, pt_info->pt);
		if (shaded == 1)
			return (SHADED);
		cur = cur->next;
	}
	return (NOT_SHADED);
}
