/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hyperboloid_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:24:38 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 17:51:42 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	fill_hy_center(t_hy *new_hy, char **info, int cv_flag)
{
	char	**center_arr;
	int		i;

	center_arr = check_commas_split(info[0]);
	if (ft_strsetlen(center_arr) != 3)
		is_error("Invalid configuration (HY CENTER)", NULL, EXIT_FAILURE);
	i = -1;
	while (center_arr[++i])
	{
		new_hy->center[i] = ft_atod(center_arr[i], &cv_flag) * 10;
		if (cv_flag)
			is_error("Invalid configuration (HY CENTER)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)center_arr);
}

static void	fill_hy_o_vect(t_hy *new_hy, char **info, int cv_flag)
{
	char	**o_vect_arr;
	int		i;

	o_vect_arr = check_commas_split(info[1]);
	if (ft_strsetlen(o_vect_arr) != 3)
		is_error("Invalid configuration (HY O_VECT)", NULL, EXIT_FAILURE);
	i = -1;
	while (o_vect_arr[++i])
	{
		new_hy->o_vect[i] = ft_atod(o_vect_arr[i], &cv_flag);
		if (cv_flag || new_hy->o_vect[i] < -1 || new_hy->o_vect[i] > 1)
			is_error("Invalid configuration (HY O_VECT)", NULL, EXIT_FAILURE);
	}
	normalize_vect(new_hy->o_vect);
	free_double_ptr((void **)o_vect_arr);
}

static void	fill_hy_color(t_hy *new_hy, char **info)
{
	char	**color_arr;
	int		i;

	color_arr = check_commas_split(info[6]);
	if (ft_strsetlen(color_arr) != 3)
		is_error("Invalid configuration (HY COLOR)", NULL, EXIT_FAILURE);
	i = -1;
	while (color_arr[++i])
	{
		if (!ft_isint(color_arr[i]))
			is_error("Invalid configuration (HY COLOR)", NULL, EXIT_FAILURE);
		new_hy->color[i] = ft_atoi(color_arr[i]);
		if ((new_hy->color[i] == 0 && color_arr[i][0] != '0')
			|| new_hy->color[i] < 0 || new_hy->color[i] > 255)
			is_error("Invalid configuration (HY COLOR)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)color_arr);
}

void	fill_hyperboloid(t_obj_lst **hd, char **info, int cv_flag)
{
	t_hy	*new_hy;

	if (ft_strsetlen(info) != 7)
		is_error("Invalid configuration (HY ARGC)", NULL, EXIT_FAILURE);
	new_hy = (t_hy *)ft_calloc(1, sizeof(t_hy));
	obj_lst_addback(hd, obj_lst_new((void *)new_hy, HYPERBOLOID));
	fill_hy_center(new_hy, info, 0);
	fill_hy_o_vect(new_hy, info, 0);
	new_hy->a = ft_atod(info[2], &cv_flag);
	if (cv_flag)
		is_error("Invalid configuration (HY A)", NULL, EXIT_FAILURE);
	new_hy->b = ft_atod(info[3], &cv_flag);
	if (cv_flag)
		is_error("Invalid configuration (HY B)", NULL, EXIT_FAILURE);
	new_hy->diameter = ft_atod(info[4], &cv_flag) * 10;
	new_hy->radius = new_hy->diameter / 2;
	if (cv_flag || new_hy->diameter < 0)
		is_error("Invalid configuration (HY DIAMETER)", NULL, EXIT_FAILURE);
	new_hy->height = ft_atod(info[5], &cv_flag) * 10;
	if (cv_flag || new_hy->height < 0)
		is_error("Invalid configuration (HY HEIGHT)", NULL, EXIT_FAILURE);
	fill_hy_color(new_hy, info);
}
