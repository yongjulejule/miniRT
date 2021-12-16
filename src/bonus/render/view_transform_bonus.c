/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:08:46 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/16 18:05:59 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	get_transf_matrix(double *vp, double *transf)
{
	double	ref[4];

	fill_vect(ref, transf[X], transf[X + 1], transf[X + 2]);
	transf[3] = -1 * dot_product(ref, vp);
	fill_vect(ref, transf[Y * 4], transf[Y * 4 + 1], transf[Y * 4 + 2]);
	transf[7] = -1 * dot_product(ref, vp);
	fill_vect(ref, transf[Z * 4], transf[Z * 4 + 1], transf[Z * 4 + 2]);
	transf[11] = -1 * dot_product(ref, vp);
	fill_vect(ref, 0, 0, 0);
	update_vect(transf, ref, W, 4);
	transf[15] = 1;
}

static void	transf_cam_lights(t_spec *spec, double *transf)
{
	t_l_lst	*cur;

	cur = spec->l_lst->next;
	while (cur)
	{
		multiply_vect(transf, cur->lp, POINT);
		cur = cur->next;
	}
	multiply_vect(transf, spec->cam.o_vect, VECTOR);
}

static void	transf_objs(t_spec *spec, t_obj_lst *cur, double *transf)
{
	while (cur)
	{
		if (cur->type == SPHERE)
			multiply_vect(transf, cur->obj.sph->center, POINT);
		else if (cur->type == PLANE)
		{
			multiply_vect(transf, cur->obj.pl->center, POINT);
			multiply_vect(transf, cur->obj.pl->o_vect, VECTOR);
		}
		else if (cur->type == CYLINDER)
		{
			multiply_vect(transf, cur->obj.cy->center, POINT);
			multiply_vect(transf, cur->obj.cy->o_vect, VECTOR);
			fill_cy_circle(cur->obj.cy, spec->cam.o_vect);
		}
		else if (cur->type == CONE)
		{
			multiply_vect(transf, cur->obj.cn->center, POINT);
			multiply_vect(transf, cur->obj.cn->o_vect, VECTOR);
			vect_copy(cur->obj.cn->circle_o_v, cur->obj.cn->o_vect);
		}
		cur = cur->next;
	}
}

void	view_transform(t_rt *rt)
{
	double	transf[16];

	get_coord_system(rt->spec, transf);
	get_transf_matrix(rt->spec->cam.vp, transf);
	transf_cam_lights(rt->spec, transf);
	transf_objs(rt->spec, rt->spec->obj_lst->next, transf);
}
