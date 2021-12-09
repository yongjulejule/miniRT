/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:49:32 by ghan              #+#    #+#             */
/*   Updated: 2021/12/09 10:41:50 by yongjule         ###   ########.fr       */
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
# define CY_CIRCLE 3

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

# define POINT 0
# define VECTOR 1

# define SHADED 0
# define NOT_SHADED 1

/* Functions */

/* Parse */
char		**check_commas_split(char *vect);
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
int			get_phong_light(t_rt *rt, t_pt_info *pt_info);
int			get_phong_r(t_rt *rt, t_pt_info *pt_info, double *o_ray,
				double *n_vect);
int			get_phong_g(t_rt *rt, t_pt_info *pt_info, double *o_ray,
				double *n_vect);
int			get_phong_b(t_rt *rt, t_pt_info *pt_info, double *o_ray,
				double *n_vect);
void		init_rt_struct(t_rt *rt, t_spec *spec);
int			intersect_pl(double *o_vect, t_pt_info *pt_info, t_pl *pl);
void		intersect_sph(double *o_vect, t_pt_info *pt_info, t_sph *sph);
void		intersect_circle(double *ray, t_pt_info *pt_i,
				t_cy *cy, double *cam_o_v);
int			intersect_cy(double *ray, t_pt_info *pt_info, t_cy *cy);
void		ray_tracing(t_rt *rt);
void		view_transform(t_rt *rt);
double		meet_pl(double *o_vect, t_pl *pl);
double		meet_sph(double *o_vect, double *origin, t_sph *sph, double r_size);
int			get_shadow(t_rt *rt, t_pt_info *pt_info);
int			pl_shadow(double *o_vect, t_pt_info *pt_info,
				t_pl *pl, double r_size);

/* Hook */
void		hook_minirt(t_rt *rt);

/* 3D Vect Util */
void		cross_product(double *ret, double *vect_1, double *vect_2);
double		dot_product(double *vect_1, double *vect_2);
void		fill_vect(double *vect, double x, double y, double z);
double		get_distance(double x, double y);
void		get_pt_on_line(double *dst, double *pt, double *dir, double t);
void		multiply_vect(double *transf, double *dst, int which);
void		normalize_vect(double *vect);
void		sub_vect(double *vect, double *dst, double *src);
void		update_vect(double *dst, double *src, int xyz, int size);
void		vect_copy(double *dst, double *src);
double		vect_size(double *vect);

#endif
