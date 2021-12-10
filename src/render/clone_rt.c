/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:52:13 by ghan              #+#    #+#             */
/*   Updated: 2021/12/10 16:14:56 by ghan             ###   ########.fr       */
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
	n_sph->color[R] = o_sph->color[R];
	n_sph->color[G] = o_sph->color[G];
	n_sph->color[B] = o_sph->color[B];
}

static void	clone_pl(t_obj_lst **c_lst, t_pl *o_pl)
{
	t_pl	*n_pl;

	n_pl = (t_pl *)ft_calloc(sizeof(t_pl), 1);
	obj_lst_addback(c_lst, obj_lst_new((void *)n_pl, PLANE));
	vect_copy(n_pl->center, o_pl->center);
	vect_copy(n_pl->o_vect, o_pl->o_vect);
	n_pl->color[R] = o_pl->color[R];
	n_pl->color[G] = o_pl->color[G];
	n_pl->color[B] = o_pl->color[B];
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
	n_cy->color[R] = o_cy->color[R];
	n_cy->color[G] = o_cy->color[G];
	n_cy->color[B] = o_cy->color[B];
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
	c_spec->amb.color[R] = o_spec->amb.color[R];
	c_spec->amb.color[G] = o_spec->amb.color[G];
	c_spec->amb.color[B] = o_spec->amb.color[B];
	c_spec->amb.ratio = o_spec->amb.ratio;
	c_spec->cam.fov = o_spec->cam.fov;
	vect_copy(c_spec->cam.vp, o_spec->cam.vp);
	vect_copy(c_spec->cam.o_vect, o_spec->cam.o_vect);
	c_spec->light.bright = o_spec->light.bright;
	vect_copy(c_spec->light.lp, o_spec->light.lp);
	c_spec->light.color[R] = o_spec->light.color[R];
	c_spec->light.color[G] = o_spec->light.color[G];
	c_spec->light.color[B] = o_spec->light.color[B];
	clone_obj_lst(o_spec->obj_lst, &c_lst);
	c_spec->obj_lst = c_lst;
	c_rt->spec = c_spec;
	c_rt->c_to_s = WIN_W / (2 * tan(c_rt->spec->cam.fov / 2));
}
