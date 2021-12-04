/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:08:46 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/04 13:59:02 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* FIXME : Need to handle when camera orientation vector is <0, 0, -1> */
static void	get_coord_system(t_spec *spec, double *transf)
{
	double	ref[4];
	double	x_axis[4];
	double	y_axis[4];
	double	z_axis[4];

	ft_bzero(transf, sizeof(double) * 16);
	fill_vect(z_axis, -1 * spec->cam.o_vect[X], -1 * spec->cam.o_vect[Y], -1 * spec->cam.o_vect[Z]);
	update_vect(transf, z_axis, Z, 4);
	if (!spec->cam.o_vect[X] && !spec->cam.o_vect[Y]
		&& (spec->cam.o_vect[Z] == -1)) // NOTE : could be wrong
		return ;
	fill_vect(ref, 0, 1, 0);
	// cross_product(y_axis, z_axis, ref);
	// normalize_vect(y_axis);
	// update_vect(transf, y_axis, Y, 4);
	cross_product(x_axis, ref, z_axis);
	normalize_vect(x_axis);
	update_vect(transf, x_axis, X, 4);
	cross_product(y_axis, z_axis, x_axis);
	normalize_vect(y_axis);
	update_vect(transf, y_axis, Y, 4);
}

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

void	transf_obj_light(t_spec *spec, double *transf)
{
	t_obj_lst	*cur;

	cur = spec->obj_lst->next;
	while (cur)
	{
		if (cur->type == SPHERE)
			multiply_vect(transf, cur->obj.sph->center, POINT);
		else if (cur->type == PLANE)
		{
			multiply_vect(transf, cur->obj.pl->center, POINT);
			multiply_vect(transf, cur->obj.pl->o_vect, VECTOR);
			normalize_vect(cur->obj.pl->o_vect);
		}
		else if (cur->type == CYLINDER)
		{
			multiply_vect(transf, cur->obj.cy->center, POINT);
			multiply_vect(transf, cur->obj.cy->o_vect, VECTOR);
			normalize_vect(cur->obj.cy->o_vect);
		}
		cur = cur->next;
	}
	multiply_vect(transf, spec->light.lp, POINT);
	multiply_vect(transf, spec->cam.o_vect, VECTOR);
	normalize_vect(spec->cam.o_vect);
}

void	view_transform(t_rt *rt)
{
	double	transf[16];

	get_coord_system(rt->spec, transf);
	get_transf_matrix(rt->spec->cam.vp, transf);
	transf_obj_light(rt->spec, transf);
}
