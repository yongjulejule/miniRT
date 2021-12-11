/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:12:42 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 15:27:39 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	config_to_spec(t_conf *cur, t_spec *spec)
{
	int	cap_flag[2];

	ft_bzero(cap_flag, 2 * sizeof(int));
	while (cur)
	{
		if (!ft_strcmp(cur->elem, "A") && !cap_flag[0])
			fill_amb(spec, cur->info, cap_flag, 0);
		else if (!ft_strcmp(cur->elem, "C") && !cap_flag[1])
			fill_cam(spec, cur->info, cap_flag, 0);
		else if (!ft_strcmp(cur->elem, "L"))
			fill_light(&(spec->l_lst), cur->info, 0);
		else if (!ft_strcmp(cur->elem, "sp"))
			fill_sphere(&(spec->obj_lst), cur->info, 0);
		else if (!ft_strcmp(cur->elem, "pl"))
			fill_plane(&(spec->obj_lst), cur->info, 0);
		else if (!ft_strcmp(cur->elem, "cy"))
			fill_cylinder(&(spec->obj_lst), cur->info, 0);
		else if (!ft_strcmp(cur->elem, "hy"))
			fill_hyperboloid(&(spec->obj_lst), cur->info, 0);
		else
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
		cur = cur->next;
	}
	if (spec->l_lst->next == NULL)
		is_error("Invalid configuration (NO LIGHT)", NULL, EXIT_FAILURE);
}

static void	str_to_conf_elem(t_conf **hd, char *line)
{
	char	**elem_info;

	elem_info = ft_split(line, ' ');
	if (elem_info[0] == NULL)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	conf_lst_addback(hd, conf_lst_new(ft_strdup(elem_info[0]),
			ft_strsetdup(elem_info + 1)));
	free_double_ptr((void **)elem_info);
}

static void	read_config(int fd, t_conf **hd)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) > 0 || (line && *line != '\0'))
	{
		if (line && *line != '\0')
			str_to_conf_elem(hd, line);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
}

static void	decide_pl_orientation(t_spec *spec)
{
	t_obj_lst	*cur;

	cur = spec->obj_lst->next;
	while (cur)
	{
		if (cur->type == PLANE)
		{
			if (dot_product(spec->cam.o_vect, cur->obj.pl->o_vect) > 0)
				fill_vect(cur->obj.pl->o_vect, -1 * cur->obj.pl->o_vect[X],
					-1 * cur->obj.pl->o_vect[Y], -1 * cur->obj.pl->o_vect[Z]);
		}
		cur = cur->next;
	}
}

void	parse_config(int argc, char **argv, t_spec *spec)
{
	int		fd;
	t_conf	*head;

	if (argc != 2)
		is_error("miniRT can display only one scene!", NULL, EXIT_FAILURE);
	else if (!argv[1] || ft_strlen(argv[1]) < 4
		|| ft_strcmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt"))
		is_error("Invalid .rt file", NULL, EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		is_error("Open failed: ", strerror(errno), EXIT_FAILURE);
	head = conf_lst_new(NULL, NULL);
	read_config(fd, &head);
	close(fd);
	spec->obj_lst = obj_lst_new(NULL, 0);
	spec->l_lst = l_lst_new();
	config_to_spec(head->next, spec);
	decide_pl_orientation(spec);
	free_config(head);
}
