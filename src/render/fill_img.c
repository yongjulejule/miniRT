/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:30:51 by ghan              #+#    #+#             */
/*   Updated: 2021/11/24 15:22:33 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_obj_img(t_rt *rt)
{
	t_obj_lst	*cur;

	rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, WIN_W, WIN_H);
	if (!rt->bg_img.img_ptr)
		is_error("Objects image init failed", NULL, EXIT_FAILURE);
	rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr,
			&rt->obj_img.bpp, &rt->obj_img.width, &rt->obj_img.endian);
	if (!rt->bg_img.data)
		is_error("Getting objects image data failed", NULL, EXIT_FAILURE);
	cur = rt->spec->obj_lst->next;
	while (cur)
	{
		if (cur->type == SPHERE)
			create_sph_img(rt, cur->obj.sph);
		// else if (cur->type == PLANE)
		// 	create_pl_img(rt, cur->obj.pl);
		// else if (cur->type == CYLINDER)
		// 	create_cy_img(rt, cur->obj.pl);
		cur = cur->next;
	}
}

static void	init_bg_img(t_rt *rt)
{
	int	w;
	int	h;
	int	bg_color;

	bg_color = get_color(rt->spec->amb.color, rt->spec->amb.ratio);
	h = 0;
	while (h < WIN_H)
	{
		w = 0;
		while (w < WIN_W)
		{
			if (w >= WIN_W / 2 - rt->fov_w / 2 && w <= WIN_W / 2 + rt->fov_w / 2)
				rt->bg_img.data[cur_pixel(rt, w, h, BG)] = bg_color;
			w++;
		}
		h++;
	}
}

void	get_bg_img(t_rt *rt)
{
	rt->bg_img.img_ptr = mlx_new_image(rt->mlx_ptr, WIN_W, WIN_H);
	if (!rt->bg_img.img_ptr)
		is_error("Background image init failed", NULL, EXIT_FAILURE);
	rt->bg_img.data = (int *)mlx_get_data_addr(rt->bg_img.img_ptr,
			&rt->bg_img.bpp, &rt->bg_img.width, &rt->bg_img.endian);
	if (!rt->bg_img.data)
		is_error("Getting background image data failed", NULL, EXIT_FAILURE);
	init_bg_img(rt);
}
