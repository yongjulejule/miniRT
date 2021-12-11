/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:52:13 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 15:47:16 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	clone_sph(t_obj_lst **c_lst, t_sph *o_sph)
{
	t_sph	*n_sph;

	n_sph = (t_sph *)ft_calloc(sizeof(t_sph), 1);
	obj_lst_addback(c_lst, obj_lst_new((void *)n_sph, SPHERE));
	n_sph->diameter = o_sph->diameter;
	n_sph->radius = o_sph->radius;
	vect_copy(n_sph->center, o_sph->center);
	copy_color(n_sph->color, o_sph->color);
}

static void	clone_pl(t_obj_lst **c_lst, t_pl *o_pl)
{
	t_pl	*n_pl;

	n_pl = (t_pl *)ft_calloc(sizeof(t_pl), 1);
	obj_lst_addback(c_lst, obj_lst_new((void *)n_pl, PLANE));
	vect_copy(n_pl->center, o_pl->center);
	vect_copy(n_pl->o_vect, o_pl->o_vect);
	copy_color(n_pl->color, o_pl->color);
}

static void	clone_cy(t_obj_lst **c_lst, t_cy *o_cy)
{
	t_cy	*n_cy;

	n_cy = (t_cy *)ft_calloc(sizeof(t_cy), 1);
	obj_lst_addback(c_lst, obj_lst_new((void *)n_cy, CYLINDER));
	n_cy->diameter = o_cy->diameter;
	n_cy->radius = o_cy->radius;
	n_cy->height = o_cy->height;
	vect_copy(n_cy->center, o_cy->center);
	vect_copy(n_cy->o_vect, o_cy->o_vect);
	copy_color(n_cy->color, o_cy->color);
}

static void	clone_obj_lst(t_obj_lst *o_lst, t_obj_lst **c_lst)
{
	t_obj_lst	*cur;

	*c_lst = obj_lst_new(NULL, 0);
	cur = o_lst->next;
	while (cur)
	{
		if (cur->type == SPHERE)
			clone_sph(c_lst, cur->obj.sph);
		else if (cur->type == PLANE)
			clone_pl(c_lst, cur->obj.pl);
		else if (cur->type == CYLINDER)
			clone_cy(c_lst, cur->obj.cy);
		cur = cur->next;
	}
}

void	clone_rt(t_rt o_rt, t_rt *c_rt, t_spec *o_spec, t_spec *c_spec)
{
	t_obj_lst	*c_lst;

	c_rt->mlx_ptr = o_rt.mlx_ptr;
	c_rt->win_ptr = o_rt.win_ptr;
	copy_color(c_spec->amb.color, o_spec->amb.color);
	c_spec->amb.ratio = o_spec->amb.ratio;
	c_spec->cam.fov = o_spec->cam.fov;
	vect_copy(c_spec->cam.vp, o_spec->cam.vp);
	vect_copy(c_spec->cam.o_vect, o_spec->cam.o_vect);
	c_spec->light.bright = o_spec->light.bright;
	vect_copy(c_spec->light.lp, o_spec->light.lp);
	copy_color(c_spec->light.color, o_spec->light.color);
	clone_obj_lst(o_spec->obj_lst, &c_lst);
	c_spec->obj_lst = c_lst;
	c_rt->spec = c_spec;
	c_rt->c_to_s = WIN_W / (2 * tan(c_rt->spec->cam.fov / 2));
}
