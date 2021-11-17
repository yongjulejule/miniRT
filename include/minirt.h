/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:49:32 by ghan              #+#    #+#             */
/*   Updated: 2021/11/17 16:01:08 by ghan             ###   ########.fr       */
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

/* User Defines */

# define SPHERE 0
# define PLANE 1
# define CYLINDER 2

typedef struct s_conf
{
	char			*elem;
	char			**info;
	struct s_conf	*next;
}	t_conf;

typedef struct s_a_light
{
	double	ratio;
	int		color[3];
}	t_a_light;

typedef struct s_cam
{
	double	vp[3];
	double	o_vect[3];
	int		fov;
}	t_cam;

typedef struct s_light
{
	double	lp[3];
	double	bright;
	int		color[3];
}	t_light;

typedef struct s_sph
{
	double	center[3];
	double	diameter;
	int		color[3];
}	t_sph;

typedef struct s_pl
{
	double	center[3];
	double	o_vect[3];
	int		color[3];
}	t_pl;

typedef struct s_cy
{
	double	center[3];
	double	o_vect[3];
	double	diameter;
	double	height;
	int		color[3];
}	t_cy;

typedef union u_obj
{
	t_sph	*sph;
	t_pl	*pl;
	t_cy	*cy;
}	t_obj;

typedef struct s_obj_lst
{
	t_obj				obj;
	struct s_obj_lst	*next;
}	t_obj_lst;

typedef struct s_spec
{
	t_a_light	a_light;
	t_cam		cam;
	t_light		light;
	t_obj_lst	*obj_lst;
}	t_spec;

/* Functions */

/* Parse */
int			get_next_line(int fd, char **line);
void		check_config(int argc, char **argv, t_spec *spec);
t_conf		*conf_lst_new(char *elem, char **info);
t_conf		*conf_lst_last(t_conf *elem);
void		conf_lst_addback(t_conf **hd, t_conf *new);
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

#endif
