/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:59:31 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/15 15:50:22 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_phong_r(t_rt *rt, t_pt_info *pt_info, double diffuse, double reflect)
{
	double	color;
	double	amb;

	color = 0;
	if (diffuse < 0)
		diffuse = 0;
	amb = (rt->spec->amb.ratio * ((double)rt->spec->amb.color[R] / 255));
	color = ((reflect + diffuse)
			* ((double)pt_info->color[R] / 255)
			* ((double)rt->spec->light.color[R] / 255))
			* rt->spec->light.bright + amb;
	return ((int)(color * 255));
}

int	get_phong_g(t_rt *rt, t_pt_info *pt_info, double diffuse, double reflect)
{
	double	color;
	double	amb;

	color = 0;
	if (diffuse < 0)
		diffuse = 0;
	amb = (rt->spec->amb.ratio * ((double)rt->spec->amb.color[G] / 255));
		color = ((reflect + diffuse)
			* ((double)pt_info->color[G] / 255)
			* ((double)rt->spec->light.color[G] / 255))
			* rt->spec->light.bright + amb;
	return ((int)(color * 255));
}

int	get_phong_b(t_rt *rt, t_pt_info *pt_info, double diffuse, double reflect)
{
	double	color;
	double	amb;

	color = 0;
	if (diffuse < 0)
		diffuse = 0;
	amb = (rt->spec->amb.ratio * ((double)rt->spec->amb.color[B] / 255));
	color = ((reflect + diffuse)
			* ((double)pt_info->color[B] / 255)
			* ((double)rt->spec->light.color[B] / 255))
			* rt->spec->light.bright + amb;
	return ((int)(color * 255));
}
