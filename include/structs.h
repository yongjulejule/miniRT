/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:53:59 by ghan              #+#    #+#             */
/*   Updated: 2021/11/19 12:54:35 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	int					type;
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

#endif