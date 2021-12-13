/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_lst_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:36:08 by ghan              #+#    #+#             */
/*   Updated: 2021/12/14 01:59:53 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_txt_lst	*txt_lst_new(int type)
{
	t_txt_lst	*new;

	new = (t_txt_lst *)ft_calloc(1, sizeof(t_txt_lst));
	new->type = type;
	new->next = NULL;
	return (new);
}

t_txt_lst	*txt_lst_nth(t_txt_lst *nth, int n)
{
	int	i;

	i = 0;
	if (nth == NULL)
		return (NULL);
	while (i + 1 < n && nth)
	{
		nth = nth->next;
		i++;
	}
	return (nth);
}

t_txt_lst	*txt_lst_last(t_txt_lst *txt_elem)
{
	if (txt_elem == NULL)
		return (NULL);
	while (txt_elem->next)
		txt_elem = txt_elem->next;
	return (txt_elem);
}

void	txt_lst_addback(t_txt_lst **hd, t_txt_lst *new)
{
	t_txt_lst	*last;

	if (!hd || !(*hd))
		return ;
	last = txt_lst_last(*hd);
	last->next = new;
}

void	free_txt_lst(t_txt_lst *hd)
{
	t_txt_lst	*cur;
	t_txt_lst	*to_free;

	cur = hd->next;
	while (cur)
	{
		to_free = cur;
		free(cur->obj_flag);
		free(cur->f_name);
		cur = cur->next;
		free(to_free);
	}
	free(hd);
}
