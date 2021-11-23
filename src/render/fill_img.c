/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:30:51 by ghan              #+#    #+#             */
/*   Updated: 2021/11/23 14:31:04 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(int *color)
{
	return (color[R] << 16 | color[G] << 8 | color[B]);
}

static void	init_bg_img(t_rt *rt)
{
	int	w;
	int	h;
	int	bg_color;

	bg_color = get_color(rt->spec->a_light.color);
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
	rt->bg_img.img_ptr = mlx_new_image(rt->mlx_ptr, WIN_W, WIN_H);
	if (!rt->bg_img.img_ptr)
		is_error("Background image init failed", NULL, EXIT_FAILURE);
	rt->bg_img.data = (int *)mlx_get_data_addr(rt->bg_img.img_ptr,
			&rt->bg_img.bpp, &rt->bg_img.width, &rt->bg_img.endian);
	if (!rt->bg_img.data)
		is_error("Getting background image data failed", NULL, EXIT_FAILURE);
	init_bg_img(rt);
}
