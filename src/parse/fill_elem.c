/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:15:55 by ghan              #+#    #+#             */
/*   Updated: 2021/11/16 21:16:34 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_a_light(t_spec *spec, char **info, int *cap_flag, int cv_flag)
{
	char	**color_arr;
	int		i;

	if (ft_strsetlen(info) != 2)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	cap_flag[0]++;
	spec->a_light.ratio = ft_atod(info[0], &cv_flag);
	if (cv_flag || (spec->a_light.ratio > 1 || spec->a_light.ratio < 0))
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	color_arr = ft_split(info[1], ',');
	if (ft_strsetlen(color_arr) != 3)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	i = -1;
	while (color_arr[++i])
	{
		if (ft_isint(color_arr[i]))
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
		spec->a_light.color[i] = ft_atoi(color_arr[i]);
		if (spec->a_light.color[i] > 255 || spec->a_light.color[i] < 0)
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)color_arr);
}

void	fill_cam(t_spec *spec, char **info, int *cap_flag, int cv_flag)
{
	if (ft_strsetlen(info) != 3)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
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
