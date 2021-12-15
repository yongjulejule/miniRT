/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_lst_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:51:28 by ghan              #+#    #+#             */
/*   Updated: 2021/12/15 12:30:25 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_obj_lst	*obj_lst_new(void *object, int which)
{
	t_obj_lst	*new;

	new = (t_obj_lst *)ft_calloc(1, sizeof(t_obj_lst));
	if (which == SPHERE)
		new->obj.sph = (t_sph *)object;
	else if (which == PLANE)
		new->obj.pl = (t_pl *)object;
	else if (which == CYLINDER)
		new->obj.cy = (t_cy *)object;
	else if (which == CONE)
		new->obj.cn = (t_cn *)object;
	new->type = which;
	new->next = NULL;
	return (new);
}

t_obj_lst	*obj_lst_last(t_obj_lst *obj_elem)
{
	if (obj_elem == NULL)
		return (NULL);
	while (obj_elem->next)
		obj_elem = obj_elem->next;
	return (obj_elem);
}

void	obj_lst_addback(t_obj_lst **hd, t_obj_lst *new)
{
	t_obj_lst	*last;

	if (!hd || !(*hd))
		return ;
	last = obj_lst_last(*hd);
	last->next = new;
}

void	free_obj_lst(t_obj_lst *hd)
{
	t_obj_lst	*cur;
	t_obj_lst	*to_free;

	cur = hd->next;
	while (cur)
	{
		to_free = cur;
		if (cur->type == SPHERE)
			free(cur->obj.sph);
		else if (cur->type == PLANE)
			free(cur->obj.pl);
		else if (cur->type == CYLINDER)
			free(cur->obj.cy);
		else if (cur->type == CONE)
			free(cur->obj.cn);
		cur = cur->next;
		free(to_free);
		to_free = NULL;
	}
	free(hd);
	hd = NULL;
}
