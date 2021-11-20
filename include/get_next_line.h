/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 09:46:25 by ghan              #+#    #+#             */
/*   Updated: 2021/11/21 00:47:54 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define HEAD_ELEM -2

typedef struct s_gnl_lst
{
	int					fd;
	char				*backup;
	struct s_gnl_lst	*next;
}				t_gnl_lst;

void			gnl_lstadd_back(t_gnl_lst **lst, t_gnl_lst *new);
t_gnl_lst		*gnl_lstnew(void *content, int fd);
void			clear_lst(t_gnl_lst **fd_lst, t_gnl_lst *cur_fd);

#endif
