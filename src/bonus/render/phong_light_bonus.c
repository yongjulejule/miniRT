/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:14:15 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/16 15:52:19 by ghan             ###   ########.fr       */
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

static void	get_surface_n_cn(double *n_vect, t_pt_info *pt_i)
{
	double	vert[3];
	double	hori[3];

	sub_vect(vert, pt_i->pt, pt_i->obj.cn->center);
	normalize_vect(vert);
	sub_vect(vert, vert, pt_i->obj.cn->o_vect);
	get_pt_on_line(vert, NULL, vert, pt_i->obj.cn->height);
	get_pt_on_line(hori, NULL, pt_i->obj.cn->o_vect, pt_i->obj.cn->radius);
	n_vect[X] = vert[X] + hori[X];
	n_vect[Y] = vert[Y] + hori[Y];
	n_vect[Z] = vert[Z] + hori[Z];
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
	else if (pt_i->type == CONE)
		get_surface_n_cn(n_vect, pt_i);
	else if (pt_i->type == CN_CIRCLE)
		vect_copy(n_vect, pt_i->obj.cn->circle_o_v);
	normalize_vect(n_vect);
}

static void	multi_phong_rgb(t_rt *rt, t_pt_info *pt_info, double *d_color)
{
	double	diffuse;
	double	reflect;
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
		diffuse = dot_product(o_ray, n_vect);
		reflect = get_reflect_light(pt_info, o_ray, n_vect);
		d_color[R] += get_phong_r(cur, pt_info, diffuse, reflect);
		d_color[G] += get_phong_g(cur, pt_info, diffuse, reflect);
		d_color[B] += get_phong_b(cur, pt_info, diffuse, reflect);
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
	if (pt_info->is_txt == CHECKERED)
		apply_checker(pt_info);
	else if (pt_info->is_txt == CUSTOM_TXT)
		apply_texture(pt_info);
	multi_phong_rgb(rt, pt_info, d_color);
	color[R] = d_color[R] * 255;
	color[G] = d_color[G] * 255;
	color[B] = d_color[B] * 255;
	check_rgb_range(color);
	return (get_color(color, 1));
}
