/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:49:32 by ghan              #+#    #+#             */
/*   Updated: 2021/11/23 14:32:02 by ghan             ###   ########.fr       */
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
# include "libft.h"
# include "structs.h"
# include "mlx.h"

/* User Defines */

# define SPHERE 0
# define PLANE 1
# define CYLINDER 2

# define X 0
# define Y 1
# define Z 2

# define R 0
# define G 1
# define B 2

/* Functions */

/* Parse */
int			get_next_line(int fd, char **line);
void		parse_config(int argc, char **argv, t_spec *spec);
t_conf		*conf_lst_new(char *elem, char **info);
t_conf		*conf_lst_last(t_conf *elem);
void		conf_lst_addback(t_conf **hd, t_conf *new);
void		free_config(t_conf *hd);
t_obj_lst	*obj_lst_new(void *object, int which);
t_obj_lst	*obj_lst_last(t_obj_lst *obj);
void		obj_lst_addback(t_obj_lst **hd, t_obj_lst *new);

/* Fill Elements */
void		fill_a_light(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_cam(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_light(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_sphere(t_obj_lst **hd, char **info, int cv_flag);
void		fill_plane(t_obj_lst **hd, char **info, int cv_flag);
void		fill_cylinder(t_obj_lst **hd, char **info, int cv_flag);

/* Render */
void		init_rt_struct(t_rt *rt, t_spec *spec);
int			get_color(int *color);
void		get_bg_img(t_rt *rt);

#endif
