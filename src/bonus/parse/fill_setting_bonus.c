/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_setting_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:23:37 by ghan              #+#    #+#             */
/*   Updated: 2021/12/13 22:40:22 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	fill_amb(t_spec *spec, char **info, int *unique, int cv_flag)
{
	char	**color_arr;
	int		i;

	if (ft_strsetlen(info) != 2)
		is_error("Invalid configuration (A ARGC)", NULL, EXIT_FAILURE);
	unique[0]++;
	spec->amb.ratio = ft_atod(info[0], &cv_flag);
	if (cv_flag || (spec->amb.ratio > 1 || spec->amb.ratio < 0))
		is_error("Invalid configuration (A RATIO)", NULL, EXIT_FAILURE);
	color_arr = trail_n_cons_del_split_split(info[1], ',');
	if (ft_strsetlen(color_arr) != 3)
		is_error("Invalid configuration (A COLOR)", NULL, EXIT_FAILURE);
	i = -1;
	while (color_arr[++i])
	{
		spec->amb.color[i] = ft_pos_atoi(color_arr[i]);
		if ((spec->amb.color[i] == 0 && color_arr[i][0] != '0')
			|| spec->amb.color[i] > 255 || spec->amb.color[i] < 0)
			is_error("Invalid configuration (A_COLOR)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)color_arr);
}

static void	fill_cam_two(t_spec *spec, char **info, int cv_flag)
{
	char	**o_vect_arr;
	int		i;

	o_vect_arr = trail_n_cons_del_split_split(info[1], ',');
	if (ft_strsetlen(o_vect_arr) != 3)
		is_error("Invalid configuration (C O_VECT)", NULL, EXIT_FAILURE);
	i = -1;
	while (o_vect_arr[++i])
	{
		spec->cam.o_vect[i] = ft_atod(o_vect_arr[i], &cv_flag);
		if (cv_flag || spec->cam.o_vect[i] < -1 || spec->cam.o_vect[i] > 1)
			is_error("Invalid configuration (C O_VECT)", NULL, EXIT_FAILURE);
	}
	normalize_vect(spec->cam.o_vect);
	free_double_ptr((void **)o_vect_arr);
}

void	fill_cam(t_spec *spec, char **info, int *unique, int cv_flag)
{
	char	**coord_arr;
	int		i;

	if (ft_strsetlen(info) != 3)
		is_error("Invalid configuration (C ARGC)", NULL, EXIT_FAILURE);
	unique[1]++;
	coord_arr = trail_n_cons_del_split_split(info[0], ',');
	if (ft_strsetlen(coord_arr) != 3)
		is_error("Invalid configuration (C VP)", NULL, EXIT_FAILURE);
	i = -1;
	while (coord_arr[++i])
	{
		spec->cam.vp[i] = ft_atod(coord_arr[i], &cv_flag) * 10;
		if (cv_flag)
			is_error("Invalid configuration (C VP)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)coord_arr);
	fill_cam_two(spec, info, 0);
	spec->cam.fov = ft_atod(info[2], &cv_flag);
	if (cv_flag || spec->cam.fov < 0 || spec->cam.fov > 180)
		is_error("Invalid configuration (C FOV)", NULL, EXIT_FAILURE);
	spec->cam.fov *= M_PI / 180;
}
