/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:54:20 by ghan              #+#    #+#             */
/*   Updated: 2021/12/06 11:30:07 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_vect(double *dst, double *src, int xyz, int size)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		dst[size * xyz + i] = src[i];
		i++;
	}
}

void	fill_vect(double *vect, double x, double y, double z)
{
	vect[X] = x;
	vect[Y] = y;
	vect[Z] = z;
}

double	vect_size(double *vect)
{
	return (sqrt(pow(vect[X], 2) + pow(vect[Y], 2) + pow(vect[Z], 2)));
}

void	get_pt_on_line(double *dst, double *pt, double *dir, double t)
{
	if (!pt)
	{
		dst[X] = dir[X] * t;
		dst[Y] = dir[Y] * t;
		dst[Z] = dir[Z] * t;
	}
	else
	{
		dst[X] = pt[X] + dir[X] * t;
		dst[Y] = pt[Y] + dir[Y] * t;
		dst[Z] = pt[Z] + dir[Z] * t;
	}
}
