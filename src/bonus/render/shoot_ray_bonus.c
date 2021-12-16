/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:07:45 by ghan              #+#    #+#             */
/*   Updated: 2021/12/16 16:07:52 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	ray_obj_intersect(t_rt *rt, double *ray,
				t_pt_info *pt_info, t_obj_lst *cur)
{
	int	meet;

	meet = 0;
	if (cur->type == SPHERE)
		meet = intersect_sph(ray, pt_info, cur->obj.sph);
	else if (cur->type == PLANE)
		meet = intersect_pl(ray, pt_info, cur->obj.pl);
	else if (cur->type == CYLINDER)
	{
		meet = intersect_cy(ray, pt_info, cur->obj.cy);
		if (!meet)
			meet = intersect_cy_circle(ray, pt_info, cur->obj.cy);
	}
	else if (cur->type == CONE)
	{
		if (dot_product(rt->spec->cam.o_vect, cur->obj.cn->o_vect) > 0)
		{
			meet = intersect_cn_circle(ray, pt_info, cur->obj.cn);
			if (!meet)
				meet = intersect_cn(ray, pt_info, cur->obj.cn);
		}
		else
		{
			meet = intersect_cn(ray, pt_info, cur->obj.cn);
			if (!meet)
				meet = intersect_cn_circle(ray, pt_info, cur->obj.cn);
		}
	}
	return (meet);
}

int	shoot_ray(t_rt *rt, double vs_x, double vs_y)
{
	double		ray[3];
	t_obj_lst	*cur;
	t_pt_info	pt_info;
	int			meet;

	pt_info.pt[Z] = 1;
	fill_vect(ray, vs_x, vs_y, -1 * rt->c_to_s);
	normalize_vect(ray);
	cur = rt->spec->obj_lst->next;
	while (cur)
	{
		meet = ray_obj_intersect(rt, ray, &pt_info, cur);
		if (meet)
			pt_info.is_txt = cur->is_txt;
		if (meet && cur->is_txt == CUSTOM_TXT)
		{
			pt_info.ppm.size[X] = cur->ppm.size[X];
			pt_info.ppm.size[Y] = cur->ppm.size[Y];
			pt_info.ppm.color_arr = cur->ppm.color_arr;
		}
		cur = cur->next;
	}
	if (pt_info.pt[Z] < 1)
		return (get_phong_light(rt, &pt_info));
	return (TRANSPARENT);
}
