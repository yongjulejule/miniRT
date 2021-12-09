/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:48:45 by ghan              #+#    #+#             */
/*   Updated: 2021/12/09 15:04:16 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw(t_rt *rt)
{
	rt->c_to_s = WIN_W / (2 * tan(rt->spec->cam.fov / 2));
	view_transform(rt);
	ray_tracing(rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr,
		rt->obj_img.img_ptr, 0, 0);
	mlx_destroy_image(rt->mlx_ptr, rt->obj_img.img_ptr);
}

int	main(int argc, char *argv[])
{
	t_spec	spec;
	t_rt	rt;

	parse_config(argc, argv, &spec);
	init_rt_struct(&rt, &spec);
	draw(&rt);
	hook_minirt(&rt);
	mlx_loop(rt.mlx_ptr);
	return (EXIT_SUCCESS);
}
