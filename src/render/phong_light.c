/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:14:15 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/02 12:56:59 by yongjule         ###   ########.fr       */
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

static void	phong_rgb(t_rt *rt, t_pt_info *pt_info, int *color)
{
	double	n_vect[3];
	double	o_ray[3];
	int		i;
	int		shadow;

	sub_vect(n_vect, pt_info->pt, pt_info->obj.sph->center);
	normalize_vect(n_vect);
	sub_vect(o_ray, rt->spec->light.lp, pt_info->pt);
	normalize_vect(o_ray);
	shadow = 1;
	i = 0;
	while (i < 3)
	{
		color[i] = (shadow * (dot_product(o_ray, n_vect)
			* (double)rt->spec->light.color[i] / 255
				* rt->spec->light.bright)
				* pt_info->obj.sph->color[i] / 255
				+ (rt->spec->amb.ratio * (double)rt->spec->amb.color[i] / 255))
			* 255;
		i++;
	}
}

int	get_phong_light_sph(t_rt *rt, t_pt_info *pt_info)
{
	int		color[3];

	phong_rgb(rt, pt_info, color);
	check_rgb_range(color);
	return (get_color(color, 1));
}
