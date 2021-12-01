/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:49:32 by ghan              #+#    #+#             */
/*   Updated: 2021/12/01 17:09:25 by yongjule         ###   ########.fr       */
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
# define W 3

# define R 0
# define G 1
# define B 2

# define TRANSPARENT 0xff000000

# define KEY_PRESS 2
# define KEY_ESC 53
# define RED_DOT 17

/* Functions */

/* Parse */
void		conf_lst_addback(t_conf **hd, t_conf *new);
t_conf		*conf_lst_last(t_conf *elem);
t_conf		*conf_lst_new(char *elem, char **info);
void		free_config(t_conf *hd);
int			get_next_line(int fd, char **line);
void		obj_lst_addback(t_obj_lst **hd, t_obj_lst *new);
t_obj_lst	*obj_lst_last(t_obj_lst *obj);
t_obj_lst	*obj_lst_new(void *object, int which);
void		parse_config(int argc, char **argv, t_spec *spec);

/* Fill Elements */
void		fill_amb(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_cam(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_cylinder(t_obj_lst **hd, char **info, int cv_flag);
void		fill_light(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_plane(t_obj_lst **hd, char **info, int cv_flag);
void		fill_sphere(t_obj_lst **hd, char **info, int cv_flag);

/* Render */
int			cur_pixel(t_rt *rt, int w, int h);
int			get_color(int *color, double ratio);
void		get_obj_img(t_rt *rt);
int			get_phong_light_sph(t_rt *rt, t_pt_info *pt_info);
void		init_rt_struct(t_rt *rt, t_spec *spec);
void		intersect_sph(double *o_vect, t_pt_info *pt_info, t_sph *sph);
void		ray_tracing(t_rt *rt);
void		view_transform(t_rt *rt);

/* Hook */
void		hook_minirt(t_rt *rt);

/* Draw Objects */
int			color_per_pixel_sph(t_sph *sph, t_light l_info);

/* Math Util */
double		get_distance(double x, double y);

/* 3D Vect Util */
void		cross_product(double *ret, double *vect_1, double *vect_2);
double		dot_product(double *vect_1, double *vect_2);
void		fill_vect(double *vect, double x, double y, double z);
void		multiply_vect(double *transf, double *dst);
void		normalize_vect(double *vect);
void		update_vect(double *dst, double *src, int xyz, int size);
double		vect_size(double *vect);

#endif
