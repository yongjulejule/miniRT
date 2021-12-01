/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:14:15 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/01 22:37:58 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* get RGB value and make it int */

static double	phong_rgb(t_rt *rt, double *n_vect, double *o_ray, int rgb)
{
	return (dot_product(o_ray, n_vect)
		* (double)rt->spec->light.color[rgb]
		* rt->spec->light.bright
		+ rt->spec->amb.ratio * (double)rt->spec->amb.color[rgb]);
}

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

int	get_phong_light_sph(t_rt *rt, t_pt_info *pt_info)
{
	double	n_vect[3];
	double	o_ray[3];
	int		color[3];
	int		shadow;

	sub_vect(n_vect, pt_info->pt, pt_info->obj.sph->center);
	normalize_vect(n_vect);
	sub_vect(o_ray, rt->spec->light.lp, pt_info->pt);
	normalize_vect(o_ray);
	shadow = 1;
	/* Need to make R G B as [0, 1] */
	color[R] = shadow * phong_rgb(rt, n_vect, o_ray, R);
	color[G] = shadow * phong_rgb(rt, n_vect, o_ray, G);
	color[B] = shadow * phong_rgb(rt, n_vect, o_ray, B);
	check_rgb_range(color);
	return (get_color(color, 1));
}
