/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cn_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:19:16 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/14 09:46:53ongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/* 
x = ((-2 a d g^2 + 2 a d R - 2 a e g h - 2 a f g j - 2 b d g h - 2 b e h^2 + 2 b e R - 2 b f h j - 2 c d g j - 2 c e h j - 2 c f j^2 + 2 c f R) ± sqrt((2 a d g^2 - 2 a d R + 2 a e g h + 2 a f g j + 2 b d g h + 2 b e h^2 - 2 b e R + 2 b f h j + 2 c d g j + 2 c e h j + 2 c f j^2 - 2 c f R)^2 - 4 (a^2 g^2 - a^2 R + 2 a b g h + 2 a c g j + b^2 h^2 - b^2 R + 2 b c h j + c^2 j^2 - c^2 R) (d^2 g^2 - d^2 R + 2 d e g h + 2 d f g j + e^2 h^2 - e^2 R + 2 e f h j + f^2 j^2 - f^2 R)))/(2 (d^2 g^2 - d^2 R + 2 d e g h + 2 d f g j + e^2 h^2 - e^2 R + 2 e f h j + f^2 j^2 - f^2 R)) (d^2 (g^2 - R) + 2 d g (e h + f j) + e^2 (h^2 - R) + 2 e f h j + f^2 (j^2 - R)!=0)

a = (d^2 g^2 - d^2 R + 2 d e g h + 2 d f g j + e^2 h^2 - e^2 R + 2 e f h j + f^2 j^2 - f^2 R)
b = (-2 a d g^2 + 2 a d R - 2 a e g h - 2 a f g j - 2 b d g h - 2 b e h^2 + 2 b e R - 2 b f h j - 2 c d g j - 2 c e h j - 2 c f j^2 + 2 c f R)
c = (a^2 g^2 - a^2 R + 2 a b g h + 2 a c g j + b^2 h^2 - b^2 R + 2 b c h j + c^2 j^2 - c^2 R)

where	a, b, c = o_cam - obj.center
		d, e, f = ray
		g, h, j = obj.o_vect
		R = cos(arctan(rad / height))^2
*/

static double	get_pt_on_cn(double *r, t_cn *cn, double *origin, double *center)
{
	double	under;
	double	coef[3];
	double	o[3];

	under = pow(cos(atan(cn->radius / cn->height)), 2);
	sub_vect(o, origin, center);
	coef[0] = (pow(r[X] * cn->o_vect[X], 2) - pow(r[X], 2) * under
			+ 2 * r[X] * r[Y] * cn->o_vect[X] * cn->o_vect[Y]
			+ 2 * r[X] * r[Z] * cn->o_vect[X] * cn->o_vect[Z]
			+ pow(r[Y] * cn->o_vect[Y], 2) - pow(r[Y], 2) * under
			+ 2 * r[Y] * r[Z] * cn->o_vect[Y] * cn->o_vect[Z]
			+ pow(r[Z] * cn->o_vect[Z], 2) - pow(r[Z], 2) * under);
	coef[1] = (-2 * o[X] * r[X] * pow(cn->o_vect[X], 2) + 2 * o[X] * r[X]
			* under - 2 * o[X] * r[Y] * cn->o_vect[X] * cn->o_vect[Y]
			- 2 * o[X] * r[Z] * cn->o_vect[X] * cn->o_vect[Z] - 2 * o[Y] * r[X]
			* cn->o_vect[X] * cn->o_vect[Y] - 2 * o[Y] * r[Y]
			* pow(cn->o_vect[Y], 2) + 2 * o[Y] * r[Y] * under
			- 2 * o[Y] * r[Z] * cn->o_vect[Y] * cn->o_vect[Z]
			- 2 * o[Z] * r[X] * cn->o_vect[X] * cn->o_vect[Z] - 2 * o[Z] * r[Y]
			* cn->o_vect[Y] * cn->o_vect[Z] - 2 * o[Z] * r[Z]
			* pow(cn->o_vect[Z], 2) + 2 * o[Z] * r[Z] * under);
	coef[2] = (pow(o[X] * cn->o_vect[X], 2) - pow(o[X], 2) * under + 2 * o[X]
			* o[Y] * cn->o_vect[X] * cn->o_vect[Y] + 2 * o[X] * o[Z]
			* cn->o_vect[X] * cn->o_vect[Z] + pow(o[Y] * cn->o_vect[Y], 2)
			- pow(o[Y], 2) * under + 2 * o[Y] * o[Z] * cn->o_vect[Y]
			* cn->o_vect[Z] + pow(o[Z] * cn->o_vect[Z], 2)
			- pow(o[Z], 2) * under);
	if (pow(coef[1], 2) - 4 * coef[0] * coef[2] < 0)
		return (0);
	return ((coef[1] - sqrt(pow(coef[1], 2) - 4 * coef[0] * coef[2]))
		/ (2 * coef[0]));
}

int	cn_shadow(double *ray, t_pt_info *pt_info, t_cn *cn, double r_size)
{
	double	t;
	double	pt[3];
	double	cur_vect[3];
	double	bottom[3];

	get_pt_on_line(bottom, cn->center, cn->o_vect, cn->height);
	t = get_pt_on_cn(ray, cn, pt_info->pt, bottom);
	if (t < 0.1 || (pt_info->pt[Z] != 1 && pt_info->pt[Z] > ray[Z] * t))
		return (0);
	get_pt_on_line(pt, pt_info->pt, ray, t);
	sub_vect(cur_vect, pt, bottom);
	if (dot_product(cur_vect, cn->o_vect) > 0
		|| pow(vect_size(cur_vect), 2) - pow(cn->radius, 2)
		> pow(cn->height, 2))
		return (0);
	if (vect_size(cur_vect) < r_size - 0.5)
		return (1);
	return (0);
}

int	intersect_cn(double *ray, t_pt_info *pt_info, t_cn *cn)
{
	double	t;
	double	pt[3];
	double	diff[3];
	double	origin[3];
	double	bottom[3];

	ft_bzero(origin, sizeof(double) * 3);
	get_pt_on_line(bottom, cn->center, cn->o_vect, cn->height);
	t = get_pt_on_cn(ray, cn, origin, bottom);
	if (t < 0.1 || (pt_info->pt[Z] != 1 && pt_info->pt[Z] > ray[Z] * t))
		return (0);
	get_pt_on_line(pt, origin, ray, t);
	sub_vect(diff, pt, bottom);
	if (dot_product(diff, cn->o_vect) > 0
		|| pow(vect_size(diff), 2) - pow(cn->radius, 2)
		> pow(cn->height, 2) + 0.5)
		return (0);
	vect_copy(pt_info->pt, pt);
	pt_info->type = CONE;
	pt_info->obj.cn = cn;
	copy_color(pt_info->color, cn->color);
	return (1);
}
