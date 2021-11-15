/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:49:32 by ghan              #+#    #+#             */
/*   Updated: 2021/11/15 16:35:37 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* Include Headers */

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "get_next_line.h"
# include "../lib/libft/libft.h"

/* User Defines */

typedef struct s_conf
{
	char			*elem;
	char			**info;
	struct s_conf	*next;
}	t_conf;

/* Functions */

/* Parse */
int			get_next_line(int fd, char **line);
void		check_config(int argc, char **argv);

#endif
