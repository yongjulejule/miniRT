/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ch_txt_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:44:05 by ghan              #+#    #+#             */
/*   Updated: 2021/12/13 15:54:40 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	fill_ch(t_txt_lst **hd, char **info, int *unique)
{
	
}

static void	fill_txt_obj_flag(t_txt_lst *n_txt, char **objs_no)
{
	int	i;

	i = -1;
	while (objs_no[++i])
	{
		if (!ft_isint(objs_no[i]))
			is_error("Invalid configuration (TXT OBJ_NO)", NULL, EXIT_FAILURE);
		n_txt->obj_flag[i] = ft_pos_atoi(objs_no[i]);
		if (n_txt->obj_flag[i] < 0)
			is_error("Invalid configuration (TXT OBJ_NO)", NULL, EXIT_FAILURE);
	}
}

void	fill_txt(t_txt_lst **hd, char **info)
{
	t_txt_lst	*n_txt;
	char		**objs_no;

	if (ft_strsetlen(info) != 2)
		is_error("Invalid configuration (TXT ARGC)", NULL, EXIT_FAILURE);
	n_txt = txt_lst_new(CUSTOM_TXT);
	txt_lst_addback(hd, n_txt);
	if (ft_strlen(info[0]) < 5
		|| ft_strcmp(info[0] + ft_strlen(info[0]) - 4, ".ppm")
		is_error("Invalid configuration (TXT NAME)", NULL, EXIT_FAILURE);
	n_txt->f_name = ft_strdup(info[0]);
	objs_no = check_commas_split(info[1]);
	if (ft_strsetlen(objs_no) < 1)
			is_error("Invalid configuration (TXT OBJ_NO)", NULL, EXIT_FAILURE);
	n_txt->obj_flag = (int *)ft_calloc((size_t)ft_strsetlen(objs_no),
						sizeof(int));
	fill_txt_obj_flag(n_txt, objs_no);	
	free_double_ptr((void **)objs_no);
}
