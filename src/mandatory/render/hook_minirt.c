/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 08:47:35 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/10 14:07:23 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	close_window(void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	exit(EXIT_SUCCESS);
}

static void	get_sph_coord(t_spec *spec)
{
	spec->cam.sph_coord[RAD] = vect_size(spec->cam.vp);
	if (!spec->cam.sph_coord[RAD])
		spec->cam.sph_coord[THETA] = 0;
	else
		spec->cam.sph_coord[THETA] = acos(spec->cam.vp[Z]
				/ spec->cam.sph_coord[RAD]);
	spec->cam.sph_coord[PHI] = atan2(spec->cam.vp[Y], spec->cam.vp[X]);
}

static int	key_press(int keycode, void *param)
{
	t_rt	*rt;
	int		flag;

	rt = (t_rt *)param;
	flag = 0;
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	flag += change_fov(keycode, rt);
	get_sph_coord(rt->spec);
	flag += move_cam_pos(keycode, rt);
	if (flag)
	{
		printf("cam position : <%.2f, %.2f, %.2f>, fov : %.2f\
, orientation : <%.2f, %.2f, %.2f>\n",
			rt->spec->cam.vp[X], rt->spec->cam.vp[Y], rt->spec->cam.vp[Z],
			rt->spec->cam.fov, rt->spec->cam.o_vect[X],
			rt->spec->cam.o_vect[Y], rt->spec->cam.o_vect[Z]);
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
		draw(rt, rt->c_rt);
	}
	return (EXIT_SUCCESS);
}

static int	mouse_press(int button, int x, int y, void *param)
{
	t_rt		*rt;
	int			flag;

	rt = (t_rt *)param;
	flag = 1;
	if (button == SCR_UP)
		get_pt_on_line(rt->spec->cam.vp, rt->spec->cam.vp,
			rt->spec->cam.o_vect, 30);
	else if (button == SCR_DOWN)
		get_pt_on_line(rt->spec->cam.vp, rt->spec->cam.vp,
			rt->spec->cam.o_vect, -30);
	else
		flag = 0;
	if (flag)
	{
		printf("cam position : <%.2f, %.2f, %.2f>, fov : %.2f\
, orientation : <%.2f, %.2f, %.2f>\n",
			rt->spec->cam.vp[X], rt->spec->cam.vp[Y], rt->spec->cam.vp[Z],
			rt->spec->cam.fov, rt->spec->cam.o_vect[X],
			rt->spec->cam.o_vect[Y], rt->spec->cam.o_vect[Z]);
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
		draw(rt, rt->c_rt);
	}
	return (x + y);
}

void	hook_minirt(t_rt *rt)
{
	mlx_hook(rt->win_ptr, KEY_PRESS, 0, key_press, rt);
	mlx_hook(rt->win_ptr, MOUSE_PRESS, 0, mouse_press, rt);
	mlx_hook(rt->win_ptr, RED_DOT, 0, close_window, rt);
}
