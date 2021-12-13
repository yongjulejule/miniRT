/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_obj_lst_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:48:06 by ghan              #+#    #+#             */
/*   Updated: 2021/12/13 14:48:18 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	clone_sph(t_obj_lst **c_lst, t_sph *o_sph)
{
	t_sph	*n_sph;

	n_sph = (t_sph *)ft_calloc(1, sizeof(t_sph));
	obj_lst_addback(c_lst, obj_lst_new((void *)n_sph, SPHERE));
	n_sph->diameter = o_sph->diameter;
	n_sph->radius = o_sph->radius;
	vect_copy(n_sph->center, o_sph->center);
	copy_color(n_sph->color, o_sph->color);
}

static void	clone_pl(t_obj_lst **c_lst, t_pl *o_pl)
{
	t_pl	*n_pl;

	n_pl = (t_pl *)ft_calloc(1, sizeof(t_pl));
	obj_lst_addback(c_lst, obj_lst_new((void *)n_pl, PLANE));
	vect_copy(n_pl->center, o_pl->center);
	vect_copy(n_pl->o_vect, o_pl->o_vect);
	copy_color(n_pl->color, o_pl->color);
}

static void	clone_cy(t_obj_lst **c_lst, t_cy *o_cy)
{
	t_cy	*n_cy;

	n_cy = (t_cy *)ft_calloc(1, sizeof(t_cy));
	obj_lst_addback(c_lst, obj_lst_new((void *)n_cy, CYLINDER));
	n_cy->diameter = o_cy->diameter;
	n_cy->radius = o_cy->radius;
	n_cy->height = o_cy->height;
	vect_copy(n_cy->center, o_cy->center);
	vect_copy(n_cy->o_vect, o_cy->o_vect);
	copy_color(n_cy->color, o_cy->color);
}

static void	clone_cn(t_obj_lst **c_lst, t_cn *o_cn)
{
	t_cn	*n_cn;

	n_cn = (t_cn *)ft_calloc(1, sizeof(t_cn));
	obj_lst_addback(c_lst, obj_lst_new((void *)n_cn, CONE));
	n_cn->diameter = o_cn->diameter;
	n_cn->radius = o_cn->radius;
	n_cn->height = o_cn->height;
	vect_copy(n_cn->center, o_cn->center);
	vect_copy(n_cn->o_vect, o_cn->o_vect);
	copy_color(n_cn->color, o_cn->color);
}

void	clone_obj_lst(t_obj_lst *o_lst, t_obj_lst **c_lst)
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
		else if (cur->type == CONE)
			clone_cn(c_lst, cur->obj.cn);
		cur = cur->next;
	}
}
