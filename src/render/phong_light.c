/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:14:15 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/04 20:28:43 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_rgb_range(int *color)
{
	int	i;

	i = 0 ;
	while (i < 3)
	{
		if (color[i] > 255)
			color[i] = 255;
		else if (color[i] < 0)
			color[i] = 0;
		i++;
	}
}

static void	each_rgb_phong(int *color, double pre_cal
			, t_rt *rt, t_pt_info *pt_i)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (pt_i->type == SPHERE)
			color[i] = (pre_cal * (double)rt->spec->light.color[i] / 255
					* pt_i->obj.sph->color[i] / 255 + (rt->spec->amb.ratio
						* (double)rt->spec->amb.color[i] / 255))
				* 255;
		else if (pt_i->type == PLANE)
			color[i] = (pre_cal * (double)rt->spec->light.color[i] / 255
					* pt_i->obj.pl->color[i] / 255 + (rt->spec->amb.ratio
						* (double)rt->spec->amb.color[i] / 255))
				* 255;
		else if (pt_i->type == CYLINDER)
			color[i] = (pre_cal * (double)rt->spec->light.color[i] / 255
					* pt_i->obj.cy->color[i] / 255 + (rt->spec->amb.ratio
						* (double)rt->spec->amb.color[i] / 255))
				* 255;
		i++;
	}
}

static	double	get_shadow(t_rt *rt, t_pt_info *pt_info, t_obj_lst *cur_obj)
{
	int			shadow;
	double		o_vect[3];
	t_obj_lst	*cur;

	shadow = 0;
	sub_vect(o_vect, rt->spec->light.lp, pt_info->pt);
	cur = rt->spec->obj_lst->next;
	while (cur)
	{
		if (cur->type == SPHERE && cur != cur_obj)
			shadow += (meet_sph(o_vect, cur->obj.sph) >= 0);
		else if (cur->type == PLANE && cur != cur_obj)
			shadow += (meet_pl(o_vect, cur->obj.pl) != 0);
		// printf("%d\n", shadow);
		// else if (cur->type == CYLINDER)
		// 	intersect_cy(o_vect, &pt_info, cur->obj.cy);
		// if (shadow)
		// 	printf("shadowed\n");
		if (shadow == 2)
			return (0);
		cur = cur->next;
	}
	return (1);
}

static void	phong_rgb(t_rt *rt, t_pt_info *pt_info, int *color
		, t_obj_lst *cur_obj)
{
	double	n_vect[3];
	double	o_ray[3];
	double shadow;

	if (pt_info->type == SPHERE)
		sub_vect(n_vect, pt_info->pt, pt_info->obj.sph->center);
	else if (pt_info->type == PLANE)
		fill_vect(n_vect, pt_info->obj.pl->o_vect[X],
			pt_info->obj.pl->o_vect[Y], pt_info->obj.pl->o_vect[Z]);
	else if (pt_info->type == CYLINDER)
		fill_vect(n_vect, pt_info->obj.cy->o_vect[X],
			pt_info->obj.cy->o_vect[Y], pt_info->obj.cy->o_vect[Z]);
	normalize_vect(n_vect);
	sub_vect(o_ray, rt->spec->light.lp, pt_info->pt);
	normalize_vect(o_ray);
	shadow = get_shadow(rt, pt_info, cur_obj);
	shadow = 1;
	each_rgb_phong(color, shadow * dot_product(o_ray, n_vect)
		* rt->spec->light.bright, rt, pt_info);
}

int	get_phong_light(t_rt *rt, t_pt_info *pt_info, t_obj_lst *cur_obj)
{
	int		color[3];

	phong_rgb(rt, pt_info, color, cur_obj);
	check_rgb_range(color);
	return (get_color(color, 1));
}
