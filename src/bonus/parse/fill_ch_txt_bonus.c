/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ch_txt_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:44:05 by ghan              #+#    #+#             */
/*   Updated: 2021/12/13 23:15:34 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	fill_txt_obj_flag(t_txt_lst *n_txt, char **info, int index)
{
	char	**objs_no;
	int		i;

	objs_no = trail_n_cons_del_split_split(info[index], ',');
	if (ft_strsetlen(objs_no) < 1)
			is_error("Invalid configuration (TXT OBJ_NO)", NULL, EXIT_FAILURE);
	n_txt->obj_flag = (int *)ft_calloc((size_t)ft_strsetlen(objs_no) + 1,
						sizeof(int));
	n_txt->obj_flag[0] = ft_strsetlen(objs_no);
	i = 0;
	while (objs_no[++i])
	{
		n_txt->obj_flag[i] = ft_pos_atoi(objs_no[i]);
		if (n_txt->obj_flag[i] < 0)
			is_error("Invalid configuration (TXT OBJ_NO)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)objs_no);
}

void	fill_ch(t_txt_lst **hd, char **info, int *unique)
{
	t_txt_lst	*n_ch;

	if (ft_strsetlen(info) != 1)
		is_error("Invalid configuration (CH ARGC)", NULL, EXIT_FAILURE);
	n_ch = txt_lst_new(CHECKERED);
	txt_lst_addback(hd, n_ch);
	n_ch->f_name = NULL;
	fill_txt_obj_flag(n_ch, info, 0);	
}

void	fill_txt(t_txt_lst **hd, char **info)
{
	t_txt_lst	*n_txt;

	if (ft_strsetlen(info) != 2)
		is_error("Invalid configuration (TXT ARGC)", NULL, EXIT_FAILURE);
	n_txt = txt_lst_new(CUSTOM_TXT);
	txt_lst_addback(hd, n_txt);
	if (ft_strlen(info[0]) < 5
		|| ft_strcmp(info[0] + ft_strlen(info[0]) - 4, ".ppm"))
		is_error("Invalid configuration (TXT NAME)", NULL, EXIT_FAILURE);
	n_txt->f_name = ft_strdup(info[0]);
	fill_txt_obj_flag(n_txt, info, 1);	
}
