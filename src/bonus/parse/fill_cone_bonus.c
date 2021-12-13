/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cone_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:24:38 by ghan              #+#    #+#             */
/*   Updated: 2021/12/13 22:13:27 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	fill_cn_center(t_cn *new_cn, char **info, int cv_flag)
{
	char	**center_arr;
	int		i;

	center_arr = check_commas_split(info[0]);
	if (ft_strsetlen(center_arr) != 3)
		is_error("Invalid configuration (CN CENTER)", NULL, EXIT_FAILURE);
	i = -1;
	while (center_arr[++i])
	{
		new_cn->center[i] = ft_atod(center_arr[i], &cv_flag) * 10;
		if (cv_flag)
			is_error("Invalid configuration (CN CENTER)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)center_arr);
}

static void	fill_cn_o_vect(t_cn *new_cn, char **info, int cv_flag)
{
	char	**o_vect_arr;
	int		i;

	o_vect_arr = check_commas_split(info[1]);
	if (ft_strsetlen(o_vect_arr) != 3)
		is_error("Invalid configuration (CN O_VECT)", NULL, EXIT_FAILURE);
	i = -1;
	while (o_vect_arr[++i])
	{
		new_cn->o_vect[i] = ft_atod(o_vect_arr[i], &cv_flag);
		if (cv_flag || new_cn->o_vect[i] < -1 || new_cn->o_vect[i] > 1)
			is_error("Invalid configuration (CN O_VECT)", NULL, EXIT_FAILURE);
	}
	normalize_vect(new_cn->o_vect);
	free_double_ptr((void **)o_vect_arr);
}

static void	fill_cn_color(t_cn *new_cn, char **info)
{
	char	**color_arr;
	int		i;

	color_arr = check_commas_split(info[4]);
	if (ft_strsetlen(color_arr) != 3)
		is_error("Invalid configuration (CN COLOR)", NULL, EXIT_FAILURE);
	i = -1;
	while (color_arr[++i])
	{
		if (!ft_isint(color_arr[i]))
			is_error("Invalid configuration (CN COLOR)", NULL, EXIT_FAILURE);
		new_cn->color[i] = ft_atoi(color_arr[i]);
		if ((new_cn->color[i] == 0 && color_arr[i][0] != '0')
			|| new_cn->color[i] < 0 || new_cn->color[i] > 255)
			is_error("Invalid configuration (CN COLOR)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)color_arr);
}

void	fill_cone(t_obj_lst **hd, char **info, int cv_flag)
{
	t_cn	*new_cn;

	if (ft_strsetlen(info) != 5)
		is_error("Invalid configuration (CN ARGC)", NULL, EXIT_FAILURE);
	new_cn = (t_cn *)ft_calloc(1, sizeof(t_cn));
	obj_lst_addback(hd, obj_lst_new((void *)new_cn, CONE));
	fill_cn_center(new_cn, info, 0);
	fill_cn_o_vect(new_cn, info, 0);
	new_cn->diameter = ft_atod(info[2], &cv_flag) * 10;
	new_cn->radius = new_cn->diameter / 2;
	if (cv_flag || new_cn->diameter < 0)
		is_error("Invalid configuration (CN DIAMETER)", NULL, EXIT_FAILURE);
	new_cn->height = ft_atod(info[3], &cv_flag) * 10;
	if (cv_flag || new_cn->height < 0)
		is_error("Invalid configuration (CN HEIGHT)", NULL, EXIT_FAILURE);
	fill_cn_color(new_cn, info);
}
