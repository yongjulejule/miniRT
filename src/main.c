/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:48:45 by ghan              #+#    #+#             */
/*   Updated: 2021/12/09 20:16:26by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* FIXME : Move to parsing process later */
void	get_sph_coord(t_spec *spec)
{
	spec->cam.sph_coord[RAD] = vect_size(spec->cam.vp);
	if (!spec->cam.sph_coord[RAD])
		spec->cam.sph_coord[THETA] = 0;
	else
		spec->cam.sph_coord[THETA] = acos(spec->cam.vp[Z]
				/ spec->cam.sph_coord[RAD]);
	spec->cam.sph_coord[PHI] = atan2(spec->cam.vp[Y], spec->cam.vp[X]);
}

void	draw(t_rt *o_rt, t_rt *c_rt)
{
	clone_rt(*o_rt, c_rt, o_rt->spec, c_rt->spec);
	get_sph_coord(c_rt->spec);
	get_sph_coord(o_rt->spec);
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
		printf("cam position : <%.2f, %.2f, %.2f>, fov : %.2f\
, orientation : <%.2f, %.2f, %.2f>\n",
			o_spec.cam.vp[X], o_spec.cam.vp[Y], o_spec.cam.vp[Z],
			o_spec.cam.fov, o_spec.cam.o_vect[X],
			o_spec.cam.o_vect[Y], o_spec.cam.o_vect[Z]);
	hook_minirt(&o_rt);
	mlx_loop(o_rt.mlx_ptr);
	return (EXIT_SUCCESS);
}
