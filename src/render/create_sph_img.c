/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sph_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:53:55 by ghan              #+#    #+#             */
/*   Updated: 2021/11/24 15:22:46 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_in_circle(double w, double h, double r, int *pt_o)
{
	return (w >= pt_o[X] - get_distance(r, h - pt_o[Y])
		&& w <= pt_o[X] + get_distance(r, h - pt_o[Y])
		&& h >= pt_o[Y] - get_distance(r, w - pt_o[X])
		&& h <= pt_o[Y] + get_distance(r, w - pt_o[X]));
}

void	create_sph_img(t_rt *rt, t_sph *sph)
{
	int		w;
	int		h;
	int		circle_color;
	int		clear;
	double	r;

	clear = TRANSPARENT | get_color(rt->spec->amb.color, rt->spec->amb.ratio);
	circle_color = get_color(sph->color, 1);
	r = sph->diameter / 2;
	h = 0;
	while (h < WIN_H)
	{
		w = 0;
		while (w < WIN_W)
		{
			if (is_in_circle((double)w, (double)h, r, rt->origin))
				rt->obj_img.data[cur_pixel(rt, w, h, OBJECTS)] = circle_color;
			else
				rt->obj_img.data[cur_pixel(rt, w, h, OBJECTS)] = clear;
			w++;
		}
		h++;
	}
}
