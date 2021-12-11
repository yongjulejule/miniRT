/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:48:45 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 11:31:53 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	draw(t_rt *o_rt, t_rt *c_rt)
{
	clone_rt(*o_rt, c_rt, o_rt->spec, c_rt->spec);
	view_transform(c_rt);
	ray_tracing(c_rt);
	mlx_put_image_to_window(c_rt->mlx_ptr, c_rt->win_ptr,
		c_rt->obj_img.img_ptr, 0, 0);
	mlx_destroy_image(c_rt->mlx_ptr, c_rt->obj_img.img_ptr);
	free_obj_lst(c_rt->spec->obj_lst);
}

int	main(int argc, char *argv[])
{
	t_spec	c_spec;
	t_spec	o_spec;
	t_rt	c_rt;
	t_rt	o_rt;

	parse_config(argc, argv, &o_spec);
	init_rt_struct(&o_rt, &c_rt, &o_spec, &c_spec);
	draw(&o_rt, &c_rt);
	hook_minirt(&o_rt);
	mlx_loop(o_rt.mlx_ptr);
	return (EXIT_SUCCESS);
}
