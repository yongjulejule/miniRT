/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 08:47:35 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/09 18:56:29 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	close_window(void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	exit(EXIT_SUCCESS);
}

static	int	move_cam(int keycode, t_rt *rt)
{
	if (keycode == KEY_A)
		rt->spec->cam.vp[X] += 10;
	else if (keycode == KEY_S)
		rt->spec->cam.vp[Y] += 10;
	else if (keycode == KEY_D)
		rt->spec->cam.vp[Z] += 10;
	else if (keycode == KEY_Z)
		rt->spec->cam.vp[X] -= 10;
	else if (keycode == KEY_X)
		rt->spec->cam.vp[Y] -= 10;
	else if (keycode == KEY_C)
		rt->spec->cam.vp[Z] -= 10;
	else if (keycode == KEY_F)
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
	else
		return (0);
	return (1);
}

static int	key_press(int keycode, void *param)
{
	t_rt	*rt;
	int		flag;

	rt = (t_rt *)param;
	flag = 0;
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	flag = move_cam(keycode, rt);
	if (flag)
	{
		printf("cam position : <%.2f, %.2f, %.2f>, fov : %.2f\n",
			rt->spec->cam.vp[X], rt->spec->cam.vp[Y], rt->spec->cam.vp[Z],
			rt->spec->cam.fov);
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
			rt->spec->cam.o_vect, 5);
	else if (button == SCR_DOWN)
		get_pt_on_line(rt->spec->cam.vp, rt->spec->cam.vp,
			rt->spec->cam.o_vect, -5);
	else
		flag = 0;
	if (flag)
	{
		printf("cam position : <%.2f, %.2f, %.2f>, fov : %.2f\n",
			rt->spec->cam.vp[X], rt->spec->cam.vp[Y], rt->spec->cam.vp[Z],
			rt->spec->cam.fov);
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
