/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conf_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:16:28 by ghan              #+#    #+#             */
/*   Updated: 2021/11/16 16:10:29 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_conf	*conf_lst_new(char *elem, char **info)
{
	t_conf	*new;

	new = (t_conf *)ft_calloc(1, sizeof(t_conf));
	new->elem = elem;
	new->info = info;
	new->next = NULL;
	return (new);
}

t_conf	*conf_lst_last(t_conf *elem)
{
	if (elem == NULL)
		return (NULL);
	while (elem->next)
		elem = elem->next;
	return (elem);
}

void	conf_lst_addback(t_conf **hd, t_conf *new)
{
	t_conf	*last;

	if (!hd || !(*hd))
		return ;
	last = conf_lst_last(*hd);
	last->next = new;
}
