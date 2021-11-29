/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:28:22 by ghan              #+#    #+#             */
/*   Updated: 2021/11/29 18:21:54 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
