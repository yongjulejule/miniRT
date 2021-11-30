/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:30:06 by ghan              #+#    #+#             */
/*   Updated: 2021/11/30 17:36:32 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_rt_struct(t_rt *rt, t_spec *spec)
{
	rt->spec = spec;
	rt->mlx_ptr = mlx_init();
	if (!rt->mlx_ptr)
		is_error("Mlx pointer init failed", NULL, EXIT_FAILURE);
	rt->win_ptr = mlx_new_window(rt->mlx_ptr, WIN_W, WIN_H, "bigrt");
	if (!rt->win_ptr)
		is_error("Window pointer init failed", NULL, EXIT_FAILURE);
	rt->c_to_s = WIN_W / (2 * tan(rt->spec->cam.fov / 2));
}
