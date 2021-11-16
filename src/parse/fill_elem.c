/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:15:55 by ghan              #+#    #+#             */
/*   Updated: 2021/11/16 17:29:13 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_a_light(t_spec *spec, char **info, int *cap_flag)
{
	cap_flag[0]++;
	
}

void	fill_cam(t_spec *spec, char **info, int *cap_flag)
{
	cap_flag[1]++;
}

void	fill_light(t_spec *spec, char **info, int *cap_flag)
{
	cap_flag[2]++;
}

void	fill_sphere(t_spec *spec, char **info)
{
	
}

void	fill_plane(t_spec *spec, char **info)
{

}

void	fill_cylinder(t_spec *spec, char **info)
{
	
}
