/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:49:32 by ghan              #+#    #+#             */
<<<<<<< HEAD:include/minirt.h
/*   Updated: 2021/12/11 11:47:55 by yongjule         ###   ########.fr       */
=======
/*   Updated: 2021/12/11 11:33:36 by ghan             ###   ########.fr       */
>>>>>>> b8c2eb1148a37e9b20bf88fcc4d15d7de4e67304:include/mandatory/minirt.h
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* Include Headers */

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
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
# define CY_CIRCLE 3

# define X 0
# define Y 1
# define Z 2
# define W 3

# define R 0
# define G 1
# define B 2

# define TRANSPARENT 0xff000000

/* Key maps */
# define KEY_PRESS 2
# define KEY_ESC 53
# define RED_DOT 17
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_F 3
# define KEY_G 5
# define MOUSE_PRESS 4
# define SCR_UP 4
# define SCR_DOWN 5

/* Spherical coordinate */
# define RAD 0
# define THETA 1
# define PHI 2

# define POINT 0
# define VECTOR 1

# define SHADED 0
# define NOT_SHADED 1

# define NBR_OF_THREAD 100

/* Functions */

/* Parse */
char		**check_commas_split(char *vect);
void		conf_lst_addback(t_conf **hd, t_conf *new);
t_conf		*conf_lst_last(t_conf *elem);
t_conf		*conf_lst_new(char *elem, char **info);
void		free_config(t_conf *hd);
void		free_obj_lst(t_obj_lst *hd);
int			get_next_line(int fd, char **line);
void		obj_lst_addback(t_obj_lst **hd, t_obj_lst *new);
t_obj_lst	*obj_lst_last(t_obj_lst *obj);
t_obj_lst	*obj_lst_new(void *object, int which);
void		parse_config(int argc, char **argv, t_spec *spec);

/* Fill Elements */
void		fill_amb(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_cam(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_cylinder(t_obj_lst **hd, char **info, int cv_flag);
void		fill_cy_circle(t_cy *cy, double *cam_o_v);
void		fill_light(t_spec *spec, char **info, int *cap_flag, int cv_flag);
void		fill_plane(t_obj_lst **hd, char **info, int cv_flag);
void		fill_sphere(t_obj_lst **hd, char **info, int cv_flag);

/* Render */
void		draw(t_rt *rt, t_rt *c_rt);
int			cur_pixel(t_rt *rt, int w, int h);
int			get_color(int *color, double ratio);
int			get_phong_light(t_rt *rt, t_pt_info *pt_info);
int			get_phong_r(t_rt *rt, t_pt_info *pt_info, double *o_ray,
				double *n_vect);
int			get_phong_g(t_rt *rt, t_pt_info *pt_info, double *o_ray,
				double *n_vect);
int			get_phong_b(t_rt *rt, t_pt_info *pt_info, double *o_ray,
				double *n_vect);
void		init_rt_struct(t_rt *o_rt, t_rt *c_rt,
				t_spec *o_spec, t_spec *c_spec);
void		ray_tracing(t_rt *rt);
void		view_transform(t_rt *rt);
void		init_obj_img(t_rt *rt);

/* Intersection & Shadow */
int			circle_shadow(double *ray, t_pt_info *pt_i,
				t_cy *cy, double r_size);
int			cy_shadow(double *ray, t_pt_info *pt_i, t_cy *cy, double r_size);
int			intersect_pl(double *ray, t_pt_info *pt_info, t_pl *pl);
void		intersect_sph(double *ray, t_pt_info *pt_info, t_sph *sph);
void		intersect_circle(double *ray, t_pt_info *pt_i, t_cy *cy);
int			intersect_cy(double *ray, t_pt_info *pt_info, t_cy *cy);
double		meet_pl(double *ray, double *o_vect);
double		meet_sph(double *ray, double *origin, t_sph *sph, double r_size);
int			get_shadow(t_rt *rt, t_pt_info *pt_info);
int			pl_shadow(double *ray, t_pt_info *pt_info,
				t_pl *pl, double r_size);

/* Hook */
void		hook_minirt(t_rt *rt);
void		clone_rt(t_rt o_rt, t_rt *c_rt, t_spec *o_spec, t_spec *c_spec);
int			change_fov(int keycode, t_rt *rt);
int			move_cam_pos(int keycode, t_rt *rt);

/* 3D Vect Util */
void		cross_product(double *ret, double *vect_1, double *vect_2);
double		dot_product(double *vect_1, double *vect_2);
void		fill_vect(double *vect, double x, double y, double z);
void		get_pt_on_line(double *dst, double *pt, double *dir, double t);
void		multiply_vect(double *transf, double *dst, int which);
void		normalize_vect(double *vect);
void		sub_vect(double *vect, double *dst, double *src);
void		update_vect(double *dst, double *src, int xyz, int size);
void		vect_copy(double *dst, double *src);
double		vect_size(double *vect);

#endif
