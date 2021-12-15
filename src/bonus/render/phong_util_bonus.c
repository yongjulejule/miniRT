/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:59:31 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/15 16:02:41 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	get_reflect_light(t_pt_info *pt_i, double *o_ray, double *n_vect)
{
	double	ret;
	double	reflect[3];
	double	proj[3];
	double	view[3];

	get_pt_on_line(proj, NULL, n_vect, 2 * dot_product(o_ray, n_vect));
	sub_vect(reflect, proj, o_ray);
	normalize_vect(reflect);
	get_pt_on_line(view, NULL, pt_i->pt, -1);
	normalize_vect(view);
	ret = dot_product(reflect, view);
	if (ret < 0)
		return (0);
	return (ret);
}

double	get_phong_r(t_l_lst *cur, t_pt_info *pt_i, double diffuse,
			double reflect)
{
	double	color;

	color = 0;
	if (diffuse < 0)
		diffuse = 0;
	color = ((reflect + diffuse)
			* ((double)pt_i->color[R] / 255)
			* ((double)cur->color[R] / 255));
	return (color * cur->bright);
}

double	get_phong_g(t_l_lst *cur, t_pt_info *pt_i, double diffuse,
			double reflect)
{
	double	color;

	color = 0;
	if (diffuse < 0)
		diffuse = 0;
	color = ((reflect + diffuse)
			* ((double)pt_i->color[G] / 255)
			* ((double)cur->color[G] / 255));
	return (color * cur->bright);
}

double	get_phong_b(t_l_lst *cur, t_pt_info *pt_i, double diffuse,
			double reflect)
{
	double	color;

	color = 0;
	if (diffuse < 0)
		diffuse = 0;
	color = ((reflect + diffuse)
			* ((double)pt_i->color[B] / 255)
			* ((double)cur->color[B] / 255));
	return (color * cur->bright);
}
