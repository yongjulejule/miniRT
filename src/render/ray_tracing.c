/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:37:33 by ghan              #+#    #+#             */
/*   Updated: 2021/12/05 01:37:47 by ghan             ###   ########.fr       */
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

int	shoot_ray(t_rt *rt, double vs_x, double vs_y)
{
	double		o_vect[3];
	t_obj_lst	*cur;
	t_pt_info	pt_info;

	pt_info.pt[Z] = 1;
	fill_vect(o_vect, vs_x, vs_y, -1 * rt->c_to_s);
	normalize_vect(o_vect);
	cur = rt->spec->obj_lst->next;
	while (cur)
	{
		if (cur->type == SPHERE)
			intersect_sph(o_vect, &pt_info, cur->obj.sph);
		else if (cur->type == PLANE)
			intersect_pl(o_vect, &pt_info, cur->obj.pl);
		// TODO - CYLINDER INTERSECTION
		// else if (cur->type == CYLINDER)
		// 	intersect_cy(o_vect, &pt_info, cur->obj.cy);
		cur = cur->next;
	}
	if (pt_info.pt[Z] < 1)
		return (get_phong_light(rt, &pt_info));
	return (TRANSPARENT);
}

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
		vs_y = h - WIN_H / 2;
		while (w < WIN_W)
		{
			vs_x = w - WIN_W / 2;
			rt->obj_img.data[cur_pixel(rt, w, h)] = shoot_ray(rt, vs_x, vs_y);
			w++;
		}
		h++;
	}
}
