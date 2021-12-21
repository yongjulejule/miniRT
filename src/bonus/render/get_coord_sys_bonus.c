/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord_sys_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:02:18 by ghan              #+#    #+#             */
/*   Updated: 2021/12/22 03:16:11 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	get_vert_coord(t_spec *spec, double *transf)
{
	double	x_axis[4];
	double	y_axis[4];
	double	z_axis[4];

	fill_vect(x_axis, 1, 0, 0);
	if (spec->cam.o_vect[Y] < 0)
	{
		fill_vect(y_axis, 0, 0, 1);
		fill_vect(z_axis, 0, 1, 0);
	}
	else
	{
		fill_vect(y_axis, 0, 0, -1);
		fill_vect(z_axis, 0, -1, 0);
	}
	update_vect(transf, x_axis, X, 4);
	update_vect(transf, y_axis, Y, 4);
	update_vect(transf, z_axis, Z, 4);
}

void	get_coord_system(t_spec *spec, double *transf)
{
	double	ref[4];
	double	x_axis[4];
	double	y_axis[4];
	double	z_axis[4];

	ft_bzero(transf, sizeof(double) * 16);
	if (!spec->cam.o_vect[X] && spec->cam.o_vect[Y] && !spec->cam.o_vect[Z])
	{
		get_vert_coord(spec, transf);
		return ;
	}
	fill_vect(z_axis, -1 * spec->cam.o_vect[X],
		-1 * spec->cam.o_vect[Y], -1 * spec->cam.o_vect[Z]);
	update_vect(transf, z_axis, Z, 4);
	fill_vect(ref, 0, 1, 0);
	cross_product(x_axis, ref, z_axis);
	normalize_vect(x_axis);
	update_vect(transf, x_axis, X, 4);
	cross_product(y_axis, z_axis, x_axis);
	normalize_vect(y_axis);
	update_vect(transf, y_axis, Y, 4);
}
