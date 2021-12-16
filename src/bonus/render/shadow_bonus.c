/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 01:36:32 by ghan              #+#    #+#             */
/*   Updated: 2021/12/16 12:01:43 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	check_obj_to_ray(t_obj_lst *cur, t_pt_info *pt_i,
				double *ray, double r_size)
{
	int	shaded;

	shaded = 0;
	while (cur)
	{
		shaded = 0;
		if (cur->type == SPHERE && cur->obj.sph != pt_i->obj.sph)
			shaded = (meet_sph(ray, pt_i->pt, cur->obj.sph, r_size) >= 0);
		else if (cur->type == PLANE && cur->obj.pl != pt_i->obj.pl)
			shaded = pl_shadow(ray, pt_i, cur->obj.pl, r_size);
		else if ((cur->type == CYLINDER || cur->type == CY_CIRCLE)
			&& cur->obj.cy != pt_i->obj.cy)
		{
			shaded = cy_shadow(ray, pt_i, cur->obj.cy, r_size);
			if (!shaded)
				shaded = circle_cy_shadow(ray, pt_i, cur->obj.cy, r_size);
		}
		else if ((cur->type == CONE || cur->type == CN_CIRCLE)
			&& cur->obj.cn != pt_i->obj.cn)
		{
			shaded = cn_shadow(ray, pt_i, cur->obj.cn, r_size);
			if (!shaded)
				shaded = circle_cn_shadow(ray, pt_i, cur->obj.cn, r_size);
		}
		else if (cur->obj.cn == pt_i->obj.cn && cur->type == CN_CIRCLE)
			shaded = cn_shadow(ray, pt_i, cur->obj.cn, r_size);
		else if (cur->obj.cn == pt_i->obj.cn && cur->type == CONE)
			shaded = circle_cn_shadow(ray, pt_i, cur->obj.cn, r_size);
		if (shaded == 1)
			return (SHADED);
		cur = cur->next;
	}
	return (NOT_SHADED);
}

int	get_shadow(t_l_lst *cur_lp, t_obj_lst *hd, t_pt_info *pt_info)
{
	double		ray[3];
	double		r_size;

	sub_vect(ray, cur_lp->lp, pt_info->pt);
	r_size = vect_size(ray);
	normalize_vect(ray);
	return (check_obj_to_ray(hd->next, pt_info, ray, r_size));
}
