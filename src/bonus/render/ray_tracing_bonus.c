/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:37:33 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 12:05:37 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	init_obj_img(t_rt *rt)
{
	rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, WIN_W, WIN_H);
	if (!rt->obj_img.img_ptr)
		is_error("Objects image init failed", NULL, EXIT_FAILURE);
	rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr,
			&rt->obj_img.bpp, &rt->obj_img.width, &rt->obj_img.endian);
	if (!rt->obj_img.data)
		is_error("Getting objects image data failed", NULL, EXIT_FAILURE);
}

int	shoot_ray(t_rt *rt, double vs_x, double vs_y)
{
	double		ray[3];
	t_obj_lst	*cur;
	t_pt_info	pt_info;

	pt_info.pt[Z] = 1;
	fill_vect(ray, vs_x, vs_y, -1 * rt->c_to_s);
	normalize_vect(ray);
	cur = rt->spec->obj_lst->next;
	while (cur)
	{
		if (cur->type == SPHERE)
			intersect_sph(ray, &pt_info, cur->obj.sph);
		else if (cur->type == PLANE)
			intersect_pl(ray, &pt_info, cur->obj.pl);
		else if (cur->type == CYLINDER)
			if (!intersect_cy(ray, &pt_info, cur->obj.cy))
				intersect_circle(ray, &pt_info, cur->obj.cy);
		cur = cur->next;
	}
	if (pt_info.pt[Z] < 1)
		return (get_phong_light(rt, &pt_info));
	return (TRANSPARENT);
}

static void	*ray_tracing_multi(void *arg)
{
	static int	seek = 0;
	t_rt		*rt;
	int			w;
	int			h;
	int			max;

	rt = (t_rt *)arg;
	pthread_mutex_lock(&rt->mutex);
	seek++;
	max = seek * WIN_H / NBR_OF_THREAD;
	h = (seek - 1) * WIN_H / NBR_OF_THREAD - 1;
	if (seek > NBR_OF_THREAD - 1)
		seek = 0;
	pthread_mutex_unlock(&rt->mutex);
	while (++h < max)
	{
		w = -1;
		while (++w < WIN_W)
			rt->obj_img.data[cur_pixel(rt, w, h)]
				= shoot_ray(rt, w - WIN_W / 2, h - WIN_H / 2);
	}
	return (arg);
}

void	ray_tracing(t_rt *rt)
{
	int			err;
	int			idx;
	pthread_t	tid[NBR_OF_THREAD];

	if (NBR_OF_THREAD > WIN_W || NBR_OF_THREAD > WIN_H)
		is_error("Too many thread", NULL, EXIT_FAILURE);
	err = pthread_mutex_init(&rt->mutex, NULL);
	if (err)
		is_error(NULL, strerror(err), EXIT_FAILURE);
	idx = -1;
	while (++idx < NBR_OF_THREAD)
	{
		err = pthread_create(&tid[idx], NULL, ray_tracing_multi, rt);
		if (err)
			is_error(NULL, strerror(err), EXIT_FAILURE);
	}
	idx = -1;
	while (++idx < NBR_OF_THREAD)
	{
		err = pthread_join(tid[idx], NULL);
		if (err)
			is_error(NULL, strerror(err), EXIT_FAILURE);
	}
	pthread_mutex_destroy(&rt->mutex);
}
