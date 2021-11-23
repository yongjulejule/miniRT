/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:30:51 by ghan              #+#    #+#             */
/*   Updated: 2021/11/23 16:42:35 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_obj_img(t_rt *rt)
{
	int	w;
	int	h;
	int	test[3];
	int	circle_color;
	double r = 100;

	test[0] = 255;
	test[1] = 255;
	test[2] = 0;
	circle_color = get_color(test, 1);
	h = 0;
	while (h < WIN_H)
	{
		w = 0;
		while (w < WIN_W)
		{
			if (w >= WIN_W / 2 - (int)sqrt(fabs(pow(r, 2) - pow((double)(h - WIN_H / 2), 2))) && w <= WIN_W / 2 + (int)sqrt(fabs(pow(r, 2) - pow((double)(h - WIN_H / 2), 2)))
				&& (h >= WIN_H / 2 - (int)sqrt(fabs(pow(r, 2) - pow((double)(w - WIN_W / 2), 2))) && h <= WIN_H / 2 + (int)sqrt(fabs(pow(r, 2) - pow((double)(w - WIN_W / 2), 2)))))
				rt->obj_img.data[(h * rt->obj_img.width + w * rt->obj_img.bpp / 8) / 4]
					= circle_color;
			else
				rt->obj_img.data[(h * rt->obj_img.width + w * rt->obj_img.bpp / 8) / 4]
					= 0xff000000;
			w++;
		}
		h++;
	}
}

void	get_obj_img(t_rt *rt)
{
	rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, WIN_W, WIN_H);
	if (!rt->bg_img.img_ptr)
		is_error("Objects image init failed", NULL, EXIT_FAILURE);
	rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr,
			&rt->obj_img.bpp, &rt->obj_img.width, &rt->obj_img.endian);
	if (!rt->bg_img.data)
		is_error("Getting objects image data failed", NULL, EXIT_FAILURE);
	init_obj_img(rt);
}

static void	init_bg_img(t_rt *rt)
{
	int	w;
	int	h;
	int	bg_color;

	bg_color = get_color(rt->spec->a_light.color, rt->spec->a_light.ratio);
	h = 0;
	while (h < WIN_H)
	{
		w = 0;
		while (w < WIN_W)
		{
			rt->bg_img.data[(h * rt->bg_img.width + w * rt->bg_img.bpp / 8) / 4]
				= bg_color;
			w++;
		}
		h++;
	}
}

void	get_bg_img(t_rt *rt)
{
	rt->bg_img.img_ptr = mlx_new_image(rt->mlx_ptr,  WIN_W, WIN_H);
	if (!rt->bg_img.img_ptr)
		is_error("Background image init failed", NULL, EXIT_FAILURE);
	rt->bg_img.data = (int *)mlx_get_data_addr(rt->bg_img.img_ptr,
			&rt->bg_img.bpp, &rt->bg_img.width, &rt->bg_img.endian);
	if (!rt->bg_img.data)
		is_error("Getting background image data failed", NULL, EXIT_FAILURE);
	init_bg_img(rt);
}
