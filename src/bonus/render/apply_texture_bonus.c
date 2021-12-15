/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:39:27 by ghan              #+#    #+#             */
/*   Updated: 2021/12/15 15:30:58 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void    apply_checker(t_pt_info *pt_info)
{
    double  sines;

    sines = sin(10 * pt_info->pt[X]) * sin(10 * pt_info->pt[Y]) * sin(10 * pt_info->pt[Z]);
    if (sines > 0)
    {
        if (pt_info->type == SPHERE)
            ft_bzero(pt_info->obj.sph->color, sizeof(int) * 3);
        else if (pt_info->type == PLANE)
            ft_bzero(pt_info->obj.pl->color, sizeof(int) * 3);
        else if (pt_info->type == CYLINDER)
            ft_bzero(pt_info->obj.cy->color, sizeof(int) * 3);
        else if (pt_info->type == CONE)
            ft_bzero(pt_info->obj.cn->color, sizeof(int) * 3);
    }
}

void    apply_texture(t_pt_info *pt_info)
{
    pt_info->is_txt = CUSTOM_TXT;
}
