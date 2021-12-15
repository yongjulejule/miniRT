/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_lst_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:51:28 by ghan              #+#    #+#             */
/*   Updated: 2021/12/15 12:30:36 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_l_lst	*l_lst_new(void)
{
	t_l_lst	*new;

	new = (t_l_lst *)ft_calloc(1, sizeof(t_l_lst));
	new->next = NULL;
	return (new);
}

t_l_lst	*l_lst_last(t_l_lst *l_elem)
{
	if (l_elem == NULL)
		return (NULL);
	while (l_elem->next)
		l_elem = l_elem->next;
	return (l_elem);
}

void	l_lst_addback(t_l_lst **hd, t_l_lst *new)
{
	t_l_lst	*last;

	if (!hd || !(*hd))
		return ;
	last = l_lst_last(*hd);
	last->next = new;
}

void	free_l_lst(t_l_lst *hd)
{
	t_l_lst	*cur;
	t_l_lst	*to_free;

	cur = hd->next;
	while (cur)
	{
		to_free = cur;
		cur = cur->next;
		free(to_free);
		to_free = NULL;
	}
	free(hd);
	hd = NULL;
}
