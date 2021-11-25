/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:30:06 by ghan              #+#    #+#             */
/*   Updated: 2021/11/24 15:11:14 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	fov_applied_width(t_rt *rt)
{
	double	rad;

	if (rt->spec->cam.fov == 180)
		return (WIN_W);
	rad = rt->spec->cam.fov * M_PI / 180;
	return ((int)(2 * rt->spec->cam.vp[Z] * fabs(tan(rad / 2))));
}

void	init_rt_struct(t_rt *rt, t_spec *spec)
{
	rt->spec = spec;
	rt->mlx_ptr = mlx_init();
	if (!rt->mlx_ptr)
		is_error("Mlx pointer init failed", NULL, EXIT_FAILURE);
	rt->win_ptr = mlx_new_window(rt->mlx_ptr, WIN_W, WIN_H, "bigrt");
	if (!rt->win_ptr)
		is_error("Window pointer init failed", NULL, EXIT_FAILURE);
	rt->fov_w = fov_applied_width(rt);
	if (rt->fov_w > WIN_W)
		rt->fov_w = WIN_W;
	rt->origin[X] = WIN_W / 2;
	rt->origin[Y] = WIN_H / 2;
}
