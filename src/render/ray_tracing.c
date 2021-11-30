/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:37:33 by ghan              #+#    #+#             */
/*   Updated: 2021/11/30 16:08:50 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_obj_img(t_rt *rt)
{
	rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, WIN_W, WIN_H);
	if (!rt->obj_img.img_ptr)
		is_error("Objects image init failed", NULL, EXIT_FAILURE);
	rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr,
			&rt->obj_img.bpp, &rt->obj_img.width, &rt->obj_img.endian);
	if (!rt->obj_img.data)
		is_error("Getting objects image data failed", NULL, EXIT_FAILURE);
}

// int	shoot_ray()
// {
	
// }

void	ray_tracing(t_rt *rt)
{
	int	w;
	int	h;
	int	vs_x;
	int	vs_y;

	init_obj_img(rt);
	h = 0;
	while (h < WIN_H)
	{
		w = 0;
		vs_y = WIN_H / 2 - h;
		while (w < WIN_W)
		{
			vs_x = w - WIN_W / 2;
			// rt->obj_img.data[cur_pixel(rt, w, h)] = shoot_ray(rt, vs_x, vs_y);
			w++;
		}
		h++;
	}
}
