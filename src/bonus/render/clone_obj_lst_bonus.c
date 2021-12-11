/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_obj_lst_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:48:06 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 16:00:51 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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

static void	clone_hy(t_obj_lst **c_lst, t_hy *o_hy)
{
	t_hy	*n_hy;

	n_hy = (t_hy *)ft_calloc(sizeof(t_hy), 1);
	obj_lst_addback(c_lst, obj_lst_new((void *)n_hy, HYPERBOLOID));
	n_hy->a = o_hy->a;
	n_hy->b = o_hy->b;
	n_hy->diameter = o_hy->diameter;
	n_hy->radius = o_hy->radius;
	n_hy->height = o_hy->height;
	vect_copy(n_hy->center, o_hy->center);
	vect_copy(n_hy->o_vect, o_hy->o_vect);
	copy_color(n_hy->color, o_hy->color);
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
		else if (cur->type == HYPERBOLOID)
			clone_hy(c_lst, cur->obj.hy);
		cur = cur->next;
	}
}
