/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:05:49 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 11:28:42 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	gnl_lstadd_back(t_gnl_lst **lst, t_gnl_lst *new)
{
	t_gnl_lst	*last;

	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_gnl_lst	*gnl_lstnew(void *content, int fd)
{
	t_gnl_lst	*ret;

	ret = (t_gnl_lst *)ft_calloc(1, sizeof(t_gnl_lst));
	ret->backup = content;
	ret->fd = fd;
	ret->next = NULL;
	return (ret);
}

void	clear_lst(t_gnl_lst **fd_lst, t_gnl_lst *cur_fd)
{
	t_gnl_lst	*prev;

	prev = *fd_lst;
	while (prev->next->fd != cur_fd->fd)
		prev = prev->next;
	prev->next = cur_fd->next;
	free(cur_fd->backup);
	free(cur_fd);
	cur_fd = NULL;
	if ((*fd_lst)->next == NULL)
	{
		free(*fd_lst);
		*fd_lst = NULL;
	}
}
