/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_to_spec_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:52:22 by ghan              #+#    #+#             */
/*   Updated: 2021/12/14 17:23:57 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	setting_to_spec(t_conf *cur, t_spec *spec, int *unique)
{
	if (!ft_strcmp(cur->elem, "A") && !unique[0])
		fill_amb(spec, cur->info, unique, 0);
	else if (!ft_strcmp(cur->elem, "C") && !unique[1])
		fill_cam(spec, cur->info, unique, 0);
	else if (!ft_strcmp(cur->elem, "L"))
		fill_light(&(spec->l_lst), cur->info, 0);
}

static void	objs_to_spec(t_conf *cur, t_obj_lst **hd, int *n_obj)
{
	if (!ft_strcmp(cur->elem, "sp"))
		fill_sphere(hd, cur->info, 0);
	else if (!ft_strcmp(cur->elem, "pl"))
		fill_plane(hd, cur->info, 0);
	else if (!ft_strcmp(cur->elem, "cy"))
		fill_cylinder(hd, cur->info, 0);
	else if (!ft_strcmp(cur->elem, "cn"))
		fill_cone(hd, cur->info, 0);
	(*n_obj)++;
}

static void	txt_to_spec(t_conf *cur, t_txt_lst **hd, int *unique)
{
	if (!ft_strcmp(cur->elem, "ch") && !unique[2])
		fill_ch(hd, cur->info, unique);
	else if (!ft_strcmp(cur->elem, "tx"))
		fill_txt(hd, cur->info);
}

void	config_to_spec(t_conf *cur, t_spec *spec, int n_obj)
{
	int	unique[3];

	ft_bzero(unique, 3 * sizeof(int));
	while (cur)
	{
		if ((!ft_strcmp(cur->elem, "A") && !unique[0])
			|| (!ft_strcmp(cur->elem, "C") && !unique[1])
			|| !ft_strcmp(cur->elem, "L"))
			setting_to_spec(cur, spec, unique);
		else if (!ft_strcmp(cur->elem, "sp") || !ft_strcmp(cur->elem, "pl")
			|| !ft_strcmp(cur->elem, "cy") || !ft_strcmp(cur->elem, "cn"))
			objs_to_spec(cur, &(spec->obj_lst), &n_obj);
		else if ((!ft_strcmp(cur->elem, "ch") && !unique[2])
			|| !ft_strcmp(cur->elem, "tx"))
			txt_to_spec(cur, &(spec->txt_lst), unique);
		else
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
		cur = cur->next;
	}
	if (spec->l_lst->next == NULL)
		is_error("Invalid configuration (NO LIGHT)", NULL, EXIT_FAILURE);
	if (spec->txt_lst->next)
		txt_to_objs(spec, spec->obj_lst->next, n_obj);
}
