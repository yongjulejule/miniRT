/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:30:51 by ghan              #+#    #+#             */
/*   Updated: 2021/11/30 12:38:26 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_obj_img(t_rt *rt)
{
	t_obj_lst	*cur;

	rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, WIN_W, WIN_H);
	if (!rt->obj_img.img_ptr)
		is_error("Objects image init failed", NULL, EXIT_FAILURE);
	rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr,
			&rt->obj_img.bpp, &rt->obj_img.width, &rt->obj_img.endian);
	if (!rt->obj_img.data)
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
