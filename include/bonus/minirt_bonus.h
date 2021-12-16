/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:49:32 by ghan              #+#    #+#             */
/*   Updated: 2021/12/16 12:03:51 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

/* Include Headers */

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "get_next_line_bonus.h"
# include "libft.h"
# include "mlx.h"
# include "structs_bonus.h"

/* User Defines */

# define SPHERE 0
# define PLANE 1
# define CYLINDER 2
# define CONE 3
# define CY_CIRCLE 4
# define CN_CIRCLE 5

# define X 0
# define Y 1
# define Z 2
# define W 3

# define R 0
# define G 1
# define B 2

# define POINT 0
# define VECTOR 1

# define SHADED 0
# define NOT_SHADED 1

# define NO_TXT 0
# define CHECKERED 1
# define CUSTOM_TXT 2

# define NBR_OF_THREAD 10

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

/* Functions */

/* Parse */
void		conf_lst_addback(t_conf **hd, t_conf *new);
t_conf		*conf_lst_last(t_conf *elem);
t_conf		*conf_lst_new(char *elem, char **info);
void		config_to_spec(t_conf *cur, t_spec *spec, int n_obj);
void		free_config(t_conf *hd);
void		free_obj_lst(t_obj_lst *hd);
void		free_txt_lst(t_txt_lst *hd);
int			get_next_line(int fd, char **line);
t_l_lst		*l_lst_new(void);
t_l_lst		*l_lst_last(t_l_lst *obj_elem);
void		l_lst_addback(t_l_lst **hd, t_l_lst *new);
void		free_l_lst(t_l_lst *hd);
void		obj_lst_addback(t_obj_lst **hd, t_obj_lst *new);
t_obj_lst	*obj_lst_last(t_obj_lst *obj);
t_obj_lst	*obj_lst_new(void *object, int which);
void		parse_config(int argc, char **argv, t_spec *spec);
void		read_fill_ppm(int fd, t_txt_lst *cur, int n, int k);
char		**trail_n_cons_del_split(char *str, char delimiter);
t_txt_lst	*txt_lst_new(int type);
t_txt_lst	*txt_lst_nth(t_txt_lst *nth, int n);
t_txt_lst	*txt_lst_last(t_txt_lst *txt_elem);
void		txt_lst_addback(t_txt_lst **hd, t_txt_lst *new);
void		txt_to_objs(t_spec *spec, t_obj_lst *cur_obj, int n_obj);

/* Fill Elements */
void		fill_amb(t_spec *spec, char **info, int *unique, int cv_flag);
void		fill_cam(t_spec *spec, char **info, int *unique, int cv_flag);
void		fill_ch(t_txt_lst **hd, char **info, int *unique);
void		fill_cylinder(t_obj_lst **hd, char **info, int cv_flag);
void		fill_cy_circle(t_cy *cy, double *cam_o_v);
void		fill_cn_circle(t_cn	*cn, double *cam_o_v);
void		fill_cone(t_obj_lst **hd, char **info, int cv_flag);
void		fill_light(t_l_lst **hd, char **info, int cv_flag);
void		fill_plane(t_obj_lst **hd, char **info, int cv_flag);
void		fill_sphere(t_obj_lst **hd, char **info, int cv_flag);
void		fill_txt(t_txt_lst **hd, char **info);

/* Render */
void		apply_checker(t_pt_info *pt_info);
void		apply_texture(t_pt_info *pt_info);
void		draw(t_rt *rt, t_rt *c_rt);
int			cur_pixel(t_rt *rt, int w, int h);
int			get_color(int *color, double ratio);
void		get_coord_system(t_spec *spec, double *transf);
int			get_phong_light(t_rt *rt, t_pt_info *pt_info);
double		get_phong_r(t_l_lst *cur, t_pt_info *pt_i, double diffuse,
				double reflect);
double		get_phong_g(t_l_lst *cur, t_pt_info *pt_i, double diffuse,
				double reflect);
double		get_phong_b(t_l_lst *cur, t_pt_info *pt_i, double diffuse,
				double reflect);
double		get_reflect_light(t_pt_info *pt_i, double *o_ray, double *n_vect);
void		init_rt_struct(t_rt *o_rt, t_rt *c_rt,
				t_spec *o_spec, t_spec *c_spec);
void		ray_tracing(t_rt *rt);
void		view_transform(t_rt *rt);
void		init_obj_img(t_rt *rt);

/* Intersection & Shadow */
int			circle_cy_shadow(double *ray, t_pt_info *pt_i,
				t_cy *cy, double r_size);
int			circle_cn_shadow(double *ray, t_pt_info *pt_i,
				t_cn *cn, double r_size);
int			cy_shadow(double *ray, t_pt_info *pt_i, t_cy *cy, double r_size);
int			cn_shadow(double *ray, t_pt_info *pt_info, t_cn *cn, double r_size);
int			intersect_pl(double *ray, t_pt_info *pt_info, t_pl *pl);
int			intersect_sph(double *ray, t_pt_info *pt_info, t_sph *sph);
int			intersect_cy(double *ray, t_pt_info *pt_info, t_cy *cy);
int			intersect_cy_circle(double *ray, t_pt_info *pt_i, t_cy *cy);
int			intersect_cn(double *ray, t_pt_info *pt_info, t_cn *cn);
int			intersect_cn_circle(double *ray, t_pt_info *pt_i, t_cn *cn);
double		meet_pl(double *ray, double *o_vect);
double		meet_sph(double *ray, double *origin, t_sph *sph, double r_size);
int			get_shadow(t_l_lst *cur_lp, t_obj_lst *hd, t_pt_info *pt_info);
int			pl_shadow(double *ray, t_pt_info *pt_info,
				t_pl *pl, double r_size);

/* Hook */
void		hook_minirt(t_rt *rt);
void		clone_obj_lst(t_obj_lst *o_lst, t_obj_lst **c_lst);
void		clone_rt(t_rt o_rt, t_rt *c_rt, t_spec *o_spec, t_spec *c_spec);
void		copy_color(int *dst, int *src);
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
