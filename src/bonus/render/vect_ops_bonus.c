/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_ops_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:28:22 by ghan              #+#    #+#             */
/*   Updated: 2021/12/13 23:08:42 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	multiply_vect(double *transf, double *dst, int which)
{
	double	homo_v[4];
	int		row;

	fill_vect(homo_v, dst[X], dst[Y], dst[Z]);
	homo_v[W] = 1;
	if (which == VECTOR)
		homo_v[W] = 0;
	row = 0;
	while (row < 3)
	{
		dst[row] = transf[row * 4 + X] * homo_v[X]
			+ transf[row * 4 + Y] * homo_v[Y]
			+ transf[row * 4 + Z] * homo_v[Z]
			+ transf[row * 4 + W] * homo_v[W];
		row++;
	}
}

void	cross_product(double *ret, double *vect_1, double *vect_2)
{
	ret[X] = vect_1[Y] * vect_2[Z] - vect_1[Z] * vect_2[Y];
	ret[Y] = vect_1[Z] * vect_2[X] - vect_1[X] * vect_2[Z];
	ret[Z] = vect_1[X] * vect_2[Y] - vect_1[Y] * vect_2[X];
}

double	dot_product(double *vect_1, double *vect_2)
{
	return (vect_1[X] * vect_2[X] + vect_1[Y] * vect_2[Y]
		+ vect_1[Z] * vect_2[Z]);
}

void	normalize_vect(double *vect)
{
	double	size;

	size = vect_size(vect);
	if (!size)
		is_error("Cannot divide by 0", NULL, EXIT_FAILURE);
	vect[X] /= size;
	vect[Y] /= size;
	vect[Z] /= size;
}

void	sub_vect(double *vect, double *dst, double *src)
{
	vect[X] = dst[X] - src[X];
	vect[Y] = dst[Y] - src[Y];
	vect[Z] = dst[Z] - src[Z];
}
