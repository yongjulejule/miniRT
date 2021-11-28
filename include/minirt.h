/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:49:32 by ghan              #+#    #+#             */
/*   Updated: 2021/11/28 08:54:07 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* Include Headers */

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "structs.h"

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

# define TRANSPARENT 0xff000000

# define OBJECTS 0
# define BG 1

# define KEY_PRESS 2
# define KEY_ESC 53
# define RED_DOT 17

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
void		fill_amb(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_cam(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_light(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_sphere(t_obj_lst **hd, char **info, int cv_flag);
void		fill_plane(t_obj_lst **hd, char **info, int cv_flag);
void		fill_cylinder(t_obj_lst **hd, char **info, int cv_flag);

/* Render */
void		init_rt_struct(t_rt *rt, t_spec *spec);
int			get_color(int *color, double ratio);
int			cur_pixel(t_rt *rt, int w, int h, int flag);
void		get_bg_img(t_rt *rt);
void		get_obj_img(t_rt *rt);

/* Hook */
void		hook_minirt(t_rt *rt);

/* Draw Objects */
void		create_sph_img(t_rt *rt, t_sph *sph);
int			color_per_pixel_sph(t_sph *sph, t_light l_info);

/* Math Util */
double		get_distance(double x, double y);

#endif
