/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:04:48 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/10 14:20:49 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	move_based_angle(t_rt *rt)
{
	double	r;
	double	x;
	double	y;

	r = rt->spec->cam.sph_coord[RAD];
	x = sin(rt->spec->cam.sph_coord[THETA]) * cos(rt->spec->cam.sph_coord[PHI]);
	y = sin(rt->spec->cam.sph_coord[THETA]) * sin(rt->spec->cam.sph_coord[PHI]);
	rt->spec->cam.vp[X] = r * x;
	rt->spec->cam.vp[Y] = r * y;
	rt->spec->cam.vp[Z] = r * cos(rt->spec->cam.sph_coord[THETA]);
	rt->spec->cam.o_vect[X] = -1 * x;
	rt->spec->cam.o_vect[Y] = -1 * y;
	rt->spec->cam.o_vect[Z] = -1 * cos(rt->spec->cam.sph_coord[THETA]);
	normalize_vect(rt->spec->cam.o_vect);
}

int	move_cam_pos(int keycode, t_rt *rt)
{
	static double	sign = 1;

	if (sin(rt->spec->cam.sph_coord[THETA]) < sin(M_PI / 30))
	{
		rt->spec->cam.sph_coord[PHI] += M_PI;
		sign = -1 * sign;
	}
	if (keycode == KEY_A)
		rt->spec->cam.sph_coord[RAD] += 1;
	else if (keycode == KEY_S)
		rt->spec->cam.sph_coord[THETA] += sign * M_PI / 30;
	else if (keycode == KEY_D)
		rt->spec->cam.sph_coord[PHI] += M_PI / 30;
	else if (keycode == KEY_Z)
		rt->spec->cam.sph_coord[RAD] -= 1;
	else if (keycode == KEY_X)
		rt->spec->cam.sph_coord[THETA] -= sign * M_PI / 30;
	else if (keycode == KEY_C)
		rt->spec->cam.sph_coord[PHI] -= M_PI / 30;
	else
		return (0);
	move_based_angle(rt);
	printf("theta : %.2f, phi : %.2f, ",
		rt->spec->cam.sph_coord[THETA], rt->spec->cam.sph_coord[PHI]);
	return (1);
}

int	change_fov(int keycode, t_rt *rt)
{
	if (keycode == KEY_F)
	{
		if (rt->spec->cam.fov < M_PI)
			rt->spec->cam.fov = (rt->spec->cam.fov + (M_PI / 36));
		else
			return (0);
	}
	else if (keycode == KEY_G)
	{
		if (rt->spec->cam.fov > 0)
			rt->spec->cam.fov = (rt->spec->cam.fov - (M_PI / 36));
		else
			return (0);
	}
	return (1);
}
