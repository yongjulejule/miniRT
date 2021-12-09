/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:48:45 by ghan              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/12/09 19:00:52 by yongjule         ###   ########.fr       */
=======
/*   Updated: 2021/12/09 19:22:52 by ghan             ###   ########.fr       */
>>>>>>> f7463a75ac959e96f56f710efa9285a1e2f6cc3c
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

/* FIXME : Move to parsing process later */
void	get_sph_coord(t_spec *spec)
{
	spec->cam.sph_coord[RAD] = vect_size(spec->cam.vp);
	spec->cam.sph_coord[THETA] = acos(spec->cam.vp[Z]
			/ spec->cam.sph_coord[RAD]);
	spec->cam.sph_coord[PHI] = atan2(spec->cam.vp[Y], spec->cam.vp[X]);
}

int	main(int argc, char *argv[])
{
	t_spec	c_spec;
	t_spec	o_spec;
	t_rt	c_rt;
	t_rt	o_rt;

	parse_config(argc, argv, &o_spec);
	get_sph_coord(&spec);
	init_rt_struct(&o_rt, &c_rt, &o_spec, &c_spec);
	draw(&o_rt, &c_rt);
	hook_minirt(&o_rt);
	mlx_loop(o_rt.mlx_ptr);
	return (EXIT_SUCCESS);
}
