/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:14:15 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/13 12:28:18 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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

/* FIXME : find inner vector and find sign... x, y by circle and z is 2*t */
static void	get_surface_n_cn(double *n_vect, t_pt_info *pt_i)
{
	double	t;
	double	start[3];
	double	diff[3];

	sub_vect(diff, pt_i->pt, pt_i->obj.cn->center);
	t = pt_i->obj.cn->height;
	if (dot_product(pt_i->obj.cn->o_vect, diff) <= 0)
		t *= -1;
	get_pt_on_line(start, pt_i->obj.cn->center, pt_i->obj.cn->o_vect, t);
	if (t > 0)
		sub_vect(n_vect, start, pt_i->pt);
	else
		sub_vect(n_vect, pt_i->pt, start);
}

static void	get_surface_n_vect(double *n_vect, t_pt_info *pt_i)
{
	if (pt_i->type == SPHERE)
		sub_vect(n_vect, pt_i->pt, pt_i->obj.sph->center);
	else if (pt_i->type == PLANE)
		vect_copy(n_vect, pt_i->obj.pl->o_vect);
	else if (pt_i->type == CYLINDER)
	{
		sub_vect(n_vect, pt_i->pt, pt_i->obj.cy->center);
		normalize_vect(n_vect);
		sub_vect(n_vect, n_vect, pt_i->obj.cy->o_vect);
	}
	else if (pt_i->type == CY_CIRCLE)
		vect_copy(n_vect, pt_i->obj.cy->circle_o_v);
	// TODO - HY SURFACE NORMAL
	else if (pt_i->type == CONE)
		get_surface_n_cn(n_vect, pt_i);
	normalize_vect(n_vect);
}

static void	multi_phong_rgb(t_rt *rt, t_pt_info *pt_info, double *d_color)
{
	double	n_vect[3];
	double	o_ray[3];
	t_l_lst	*cur;

	cur = rt->spec->l_lst->next;
	while (cur)
	{
		sub_vect(o_ray, cur->lp, pt_info->pt);
		normalize_vect(o_ray);
		get_surface_n_vect(n_vect, pt_info);
		if (get_shadow(cur, rt->spec->obj_lst, pt_info) == SHADED)
		{
			cur = cur->next;
			continue ;
		}
		d_color[R] += get_phong_r(cur, pt_info, o_ray, n_vect);
		d_color[G] += get_phong_g(cur, pt_info, o_ray, n_vect);
		d_color[B] += get_phong_b(cur, pt_info, o_ray, n_vect);
		cur = cur->next;
	}
}

int	get_phong_light(t_rt *rt, t_pt_info *pt_info)
{
	double	d_color[3];
	int		color[3];

	d_color[R] = rt->spec->amb.ratio * (double)rt->spec->amb.color[R] / 255;
	d_color[G] = rt->spec->amb.ratio * (double)rt->spec->amb.color[G] / 255;
	d_color[B] = rt->spec->amb.ratio * (double)rt->spec->amb.color[B] / 255;
	multi_phong_rgb(rt, pt_info, d_color);
	color[R] = d_color[R] * 255;
	color[G] = d_color[G] * 255;
	color[B] = d_color[B] * 255;
	check_rgb_range(color);
	return (get_color(color, 1));
}
