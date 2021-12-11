/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_light_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:59:43 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 15:23:35 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	fill_light_two(t_l_lst *n_light, char **info)
{
	char	**color_arr;
	int		i;

	color_arr = check_commas_split(info[2]);
	if (ft_strsetlen(color_arr) != 3)
		is_error("Invalid configuration (L COLOR)", NULL, EXIT_FAILURE);
	i = -1;
	while (color_arr[++i])
	{
		if (!ft_isint(color_arr[i]))
			is_error("Invalid configuration (L COLOR)", NULL, EXIT_FAILURE);
		n_light->color[i] = ft_atoi(color_arr[i]);
		if ((n_light->color[i] == 0 && color_arr[i][0] != '0')
			|| n_light->color[i] > 255 || n_light->color[i] < 0)
			is_error("Invalid configuration (L COLOR)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)color_arr);
}

void	fill_light(t_l_lst **hd, char **info, int cv_flag)
{
	char		**coord_arr;
	int			i;
	t_l_lst		*n_light;

	if (ft_strsetlen(info) != 3)
		is_error("Invalid configuration (L ARGC)", NULL, EXIT_FAILURE);
	n_light = l_lst_new();
	l_lst_addback(hd, n_light);
	coord_arr = check_commas_split(info[0]);
	if (ft_strsetlen(coord_arr) != 3)
		is_error("Invalid configuration (L LP)", NULL, EXIT_FAILURE);
	i = -1;
	while (coord_arr[++i])
	{
		n_light->lp[i] = ft_atod(coord_arr[i], &cv_flag) * 10;
		if (cv_flag)
			is_error("Invalid configuration (L LP)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)coord_arr);
	n_light->bright = ft_atod(info[1], &cv_flag);
	if (cv_flag || n_light->bright < 0 || n_light->bright > 1)
		is_error("Invalid configuration (L BRIGHT)", NULL, EXIT_FAILURE);
	fill_light_two(n_light, info);
}
