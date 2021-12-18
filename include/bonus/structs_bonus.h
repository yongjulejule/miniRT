/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:53:59 by ghan              #+#    #+#             */
/*   Updated: 2021/12/18 16:56:14 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

typedef struct s_conf
{
	char			*elem;
	char			**info;
	struct s_conf	*next;
}	t_conf;

typedef struct s_amb
{
	double	ratio;
	int		color[3];
}	t_amb;

typedef struct s_cam
{
	double	vp[3];
	double	o_vect[3];
	double	fov;
	double	sph_coord[3];
}	t_cam;

typedef struct s_l_lst
{
	double			lp[3];
	double			bright;
	int				color[3];
	struct s_l_lst	*next;
}	t_l_lst;

typedef struct s_sph
{
	double	center[3];
	double	o_vect[3];
	double	diameter;
	double	radius;
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
	double	radius;
	double	height;
	int		color[3];
	double	circle_center[3];
	double	circle_o_v[3];
}	t_cy;

typedef struct s_cn
{
	double	center[3];
	double	o_vect[3];
	double	diameter;
	double	radius;
	double	height;
	int		color[3];
	double	circle_o_v[3];
}	t_cn;

typedef union u_obj
{
	t_sph	*sph;
	t_pl	*pl;
	t_cy	*cy;
	t_cn	*cn;
}	t_obj;

typedef struct s_ppm
{
	int		size[2];
	int		*color_arr;
}	t_ppm;

typedef struct s_obj_lst
{
	int					type;
	int					is_txt;
	t_obj				obj;
	t_ppm				ppm;
	struct s_obj_lst	*next;
}	t_obj_lst;

typedef struct s_txt_lst
{
	int					type;
	int					*obj_txt_flag;
	int					*obj_flag;
	char				*f_name;
	t_ppm				ppm;
	struct s_txt_lst	*next;
}	t_txt_lst;

typedef struct s_spec
{
	t_amb		amb;
	t_cam		cam;
	t_l_lst		*l_lst;
	t_obj_lst	*obj_lst;
	t_txt_lst	*txt_lst;
}	t_spec;

typedef struct s_img
{
	int		width;
	int		bpp;
	int		endian;
	int		*data;
	void	*img_ptr;
}	t_img;

typedef struct s_rt
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_spec			*spec;
	struct s_rt		*c_rt;
	double			c_to_s;
	t_img			obj_img;
	pthread_mutex_t	mutex;
}	t_rt;

typedef struct s_pt_info
{
	int			type;
	int			is_txt;
	int			color[3];
	double		pt[3];
	t_obj		obj;
	t_ppm		ppm;
}	t_pt_info;

#endif
