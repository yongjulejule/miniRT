/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 08:47:35 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/09 15:11:10 by yongjule         ###   ########.fr       */
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
		rt->spec->cam.fov = ((rt->spec->cam.fov + 0.1));
		if (rt->spec->cam.fov > M_PI)
			rt->spec->cam.fov -= M_PI;
	}
	else
		return (0);
	printf("current cam is <%d, %d, %d>, fov is %2f\n", (int)rt->spec->cam.vp[X],
		(int)rt->spec->cam.vp[Y], (int)rt->spec->cam.vp[Z], rt->spec->cam.fov);
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
	// flag += move_light(keycode, rt);
	flag += move_cam(keycode, rt);
	if (flag)
	{
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
		draw(rt);
	}
	return (EXIT_SUCCESS);
}

void	hook_minirt(t_rt *rt)
{
	mlx_hook(rt->win_ptr, KEY_PRESS, 0, key_press, rt);
	mlx_hook(rt->win_ptr, RED_DOT, 0, close_window, rt);
}
