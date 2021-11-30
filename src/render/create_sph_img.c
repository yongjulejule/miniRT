/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sph_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:53:55 by ghan              #+#    #+#             */
/*   Updated: 2021/11/30 15:34:55 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_in_circle(double w, double h, double r, int *pt_o)
{
	return (w >= pt_o[X] - get_distance(r, h - pt_o[Y])
		&& w <= pt_o[X] + get_distance(r, h - pt_o[Y])
		&& h >= pt_o[Y] - get_distance(r, w - pt_o[X])
		&& h <= pt_o[Y] + get_distance(r, w - pt_o[X]));
}
