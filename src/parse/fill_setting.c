/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_setting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:23:37 by ghan              #+#    #+#             */
/*   Updated: 2021/11/17 15:48:36 by ghan             ###   ########.fr       */
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
		if (!ft_isint(color_arr[i]))
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
		spec->a_light.color[i] = ft_atoi(color_arr[i]);
		if (spec->a_light.color[i] > 255 || spec->a_light.color[i] < 0)
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)color_arr);
}

static void	fill_cam_two(t_spec *spec, char **info, int cv_flag)
{
	char	**o_vect_arr;
	int		i;

	o_vect_arr = ft_split(info[1], ',');
	if (ft_strsetlen(o_vect_arr) != 3)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	i = -1;
	while (o_vect_arr[++i])
	{
		spec->cam.o_vect[i] = ft_atod(o_vect_arr[i], &cv_flag);
		if (cv_flag || spec->cam.o_vect[i] < -1 || spec->cam.o_vect[i] > 1)
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)o_vect_arr);
}

void	fill_cam(t_spec *spec, char **info, int *cap_flag, int cv_flag)
{
	char	**coord_arr;
	int		i;

	if (ft_strsetlen(info) != 3)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	cap_flag[1]++;
	coord_arr = ft_split(info[0], ',');
	if (ft_strsetlen(coord_arr) != 3)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	i = -1;
	while (coord_arr[++i])
	{
		spec->cam.vp[i] = ft_atod(coord_arr[i], &cv_flag);
		if (cv_flag)
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)coord_arr);
	fill_cam_two(spec, info, 0);
	if (!ft_isint(info[2]))
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	spec->cam.fov = ft_atoi(info[2]);
}

static void	fill_light_two(t_spec *spec, char **info)
{
	char	**color_arr;
	int		i;

	color_arr = ft_split(info[2], ',');
	if (ft_strsetlen(color_arr) != 3)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	i = -1;
	while (color_arr[++i])
	{
		if (!ft_isint(color_arr[i]))
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
		spec->light.color[i] = ft_atoi(color_arr[i]);
		if (spec->light.color[i] > 255 || spec->light.color[i] < 0)
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)color_arr);
}

void	fill_light(t_spec *spec, char **info, int *cap_flag, int cv_flag)
{
	char	**coord_arr;
	int		i;

	if (ft_strsetlen(info) != 3)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	cap_flag[2]++;
	coord_arr = ft_split(info[0], ',');
	if (ft_strsetlen(coord_arr) != 3)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	i = -1;
	while (coord_arr[++i])
	{
		spec->light.lp[i] = ft_atod(coord_arr[i], &cv_flag);
		if (cv_flag)
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)coord_arr);
	spec->light.bright = ft_atod(info[1], &cv_flag);
	if (cv_flag || spec->light.bright < 0 || spec->light.bright > 1)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	fill_light_two(spec, info);
}
