/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_rt_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:52:13 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 17:30:53 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	clone_l_lst(t_l_lst *o_lst, t_l_lst **c_lst)
{
	t_l_lst	*cur;
	t_l_lst	*new;

	*c_lst = l_lst_new();
	cur = o_lst->next;
	while (cur)
	{
		new = l_lst_new();
		vect_copy(new->lp, cur->lp);
		new->bright = cur->bright;
		copy_color(new->color, cur->color);
		l_lst_addback(c_lst, new);
		cur = cur->next;
	}
}

void	clone_rt(t_rt o_rt, t_rt *c_rt, t_spec *o_spec, t_spec *c_spec)
{
	t_l_lst		*c_l_lst;
	t_obj_lst	*c_obj_lst;

	c_rt->mlx_ptr = o_rt.mlx_ptr;
	c_rt->win_ptr = o_rt.win_ptr;
	copy_color(c_spec->amb.color, o_spec->amb.color);
	c_spec->amb.ratio = o_spec->amb.ratio;
	c_spec->cam.fov = o_spec->cam.fov;
	vect_copy(c_spec->cam.vp, o_spec->cam.vp);
	vect_copy(c_spec->cam.o_vect, o_spec->cam.o_vect);
	clone_l_lst(o_spec->l_lst, &c_l_lst);
	c_spec->l_lst = c_l_lst;
	clone_obj_lst(o_spec->obj_lst, &c_obj_lst);
	c_spec->obj_lst = c_obj_lst;
	c_rt->spec = c_spec;
	c_rt->c_to_s = WIN_W / (2 * tan(c_rt->spec->cam.fov / 2));
}
