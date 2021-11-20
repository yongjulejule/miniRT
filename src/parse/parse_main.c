/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:12:42 by ghan              #+#    #+#             */
/*   Updated: 2021/11/21 00:53:58 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	config_to_spec(t_conf *cur, t_spec *spec)
{
	int	cap_flag[3];

	cap_flag[0] = 0;
	cap_flag[1] = 0;
	cap_flag[2] = 0;
	spec->obj_lst = obj_lst_new(NULL, 0);
	while (cur)
	{
		if (!ft_strcmp(cur->elem, "A") && !cap_flag[0])
			fill_a_light(spec, cur->info, cap_flag, 0);
		else if (!ft_strcmp(cur->elem, "C") && !cap_flag[1])
			fill_cam(spec, cur->info, cap_flag, 0);
		else if (!ft_strcmp(cur->elem, "L") && !cap_flag[2])
			fill_light(spec, cur->info, cap_flag, 0);
		else if (!ft_strcmp(cur->elem, "sp"))
			fill_sphere(&(spec->obj_lst), cur->info, 0);
		else if (!ft_strcmp(cur->elem, "pl"))
			fill_plane(&(spec->obj_lst), cur->info, 0);
		else if (!ft_strcmp(cur->elem, "cy"))
			fill_cylinder(&(spec->obj_lst), cur->info, 0);
		else
			is_error("Invalid configuration", NULL, EXIT_FAILURE);
		cur = cur->next;
	}
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

	while (get_next_line(fd, &line) > 0)
	{
		if (line && *line != '\0')
			str_to_conf_elem(hd, line);
		free(line);
		line = NULL;
	}
	if (line && *line != '\0')
		str_to_conf_elem(hd, line);
	free(line);
	line = NULL;
}

void	parse_config(int argc, char **argv, t_spec *spec)
{
	int		fd;
	t_conf	*head;

	if (argc != 2)
		is_error("miniRT must display only one scene!", NULL, EXIT_FAILURE);
	else if (!argv[1] || ft_strlen(argv[1]) < 4
		|| ft_strcmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt"))
		is_error("Invalid .rt file", NULL, EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		is_error("Open failed: ", strerror(errno), EXIT_FAILURE);
	head = conf_lst_new(NULL, NULL);
	read_config(fd, &head);
	close(fd);
	config_to_spec(head->next, spec);
	free_config(head);
}
