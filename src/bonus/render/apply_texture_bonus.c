/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:39:27 by ghan              #+#    #+#             */
/*   Updated: 2021/12/16 17:05:35 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	apply_checker(t_pt_info *pt_info)
{
	double	sines;

	sines = sin(pt_info->pt[X] / 100) * sin(pt_info->pt[Y] / 100)
		* sin(pt_info->pt[Z] / 100);
	if (sines > 0)
		ft_bzero(pt_info->color, sizeof(int) * 3);
}

void	apply_texture(t_pt_info *pt_info)
{
	pt_info->is_txt = CUSTOM_TXT;
}
