/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:30:06 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 11:20:08 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	init_rt_struct(t_rt *o_rt, t_rt *c_rt, t_spec *o_spec, t_spec *c_spec)
{
	o_rt->spec = o_spec;
	o_rt->mlx_ptr = mlx_init();
	if (!o_rt->mlx_ptr)
		is_error("Mlx pointer init failed", NULL, EXIT_FAILURE);
	o_rt->win_ptr = mlx_new_window(o_rt->mlx_ptr, WIN_W, WIN_H, "bigrt");
	if (!o_rt->win_ptr)
		is_error("Window pointer init failed", NULL, EXIT_FAILURE);
	o_rt->c_rt = c_rt;
	c_rt->spec = c_spec;
}
