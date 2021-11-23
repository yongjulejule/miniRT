/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:48:45 by ghan              #+#    #+#             */
/*   Updated: 2021/11/23 14:30:38 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char *argv[])
{
	t_spec	spec;
	t_rt	rt;

	parse_config(argc, argv, &spec);
	init_rt_struct(&rt, &spec);
	get_bg_img(&rt);
	mlx_put_image_to_window(rt.mlx_ptr, rt.win_ptr, rt.bg_img.img_ptr, 0, 0);
	mlx_loop(rt.mlx_ptr);
	// get_obj_img();
	// draw();
	// mlx_loop(rt->mlx_ptr);
	return (EXIT_SUCCESS);
}
