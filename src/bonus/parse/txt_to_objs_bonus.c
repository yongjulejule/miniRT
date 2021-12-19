/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_to_objs_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:01:52 by ghan              #+#    #+#             */
/*   Updated: 2021/12/19 11:11:54 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	ppm_to_struct(t_txt_lst *cur)
{
	int		fd;
	char	*tmp;

	tmp = ft_strjoin("./etc/texture/", cur->f_name);
	fd = open(tmp, O_RDONLY);
	free(tmp);
	if (fd < 0)
		is_error("ppm file open failed: ", strerror(errno), EXIT_FAILURE);
	read_fill_ppm(fd, cur, 0, 0);
	close(fd);
}

static void	check_obj_txt_flag(t_txt_lst *cur, int *o_t_flag,
				int n_obj, int o_idx)
{
	int	i;

	if (cur->obj_flag[0] > n_obj)
		is_error("Invalid configuration (OBJ IDX)", NULL, EXIT_FAILURE);
	i = 0;
	while (i < cur->obj_flag[0])
	{
		if (cur->obj_flag[i + 1] >= n_obj)
			is_error("Invalid configuration (OBJ IDX)", NULL, EXIT_FAILURE);
		o_t_flag[cur->obj_flag[i + 1]] = o_idx;
		i++;
	}
	cur->obj_txt_flag = o_t_flag;
}

static void	parse_ppm(t_txt_lst *cur, int *o_t_flag, int n_obj)
{
	int	o_idx;

	o_idx = 1;
	while (cur)
	{
		check_obj_txt_flag(cur, o_t_flag, n_obj, o_idx);
		if (cur->type == CUSTOM_TXT)
			ppm_to_struct(cur);
		cur = cur->next;
		o_idx++;
	}
}

static void	fill_obj_txt_info(t_obj_lst *cur_obj, t_txt_lst *nth_txt)
{
	cur_obj->is_txt = nth_txt->type;
	if (cur_obj->is_txt == CUSTOM_TXT)
	{
		cur_obj->ppm.size[X] = nth_txt->ppm.size[X];
		cur_obj->ppm.size[Y] = nth_txt->ppm.size[Y];
		cur_obj->ppm.color_arr = nth_txt->ppm.color_arr;
	}
}

void	txt_to_objs(t_spec *spec, t_obj_lst *cur_obj, int n_obj)
{
	int			i;
	t_txt_lst	*nth_txt;

	spec->txt_lst->obj_txt_flag = (int *)ft_calloc(n_obj, sizeof(int));
	parse_ppm(spec->txt_lst->next, spec->txt_lst->obj_txt_flag, n_obj);
	i = 0;
	while (cur_obj)
	{
		if (spec->txt_lst->obj_txt_flag[i] > 0)
		{
			nth_txt = txt_lst_nth(spec->txt_lst->next,
					spec->txt_lst->obj_txt_flag[i]);
			if (!nth_txt)
				is_error("Invalid configuration (PPM TO OBJ)",
					NULL, EXIT_FAILURE);
			fill_obj_txt_info(cur_obj, nth_txt);
		}
		else
			cur_obj->is_txt = NO_TXT;
		cur_obj = cur_obj->next;
		i++;
	}
	free(spec->txt_lst->obj_txt_flag);
	free_txt_lst(spec->txt_lst);
}
