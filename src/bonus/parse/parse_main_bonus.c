/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:12:42 by ghan              #+#    #+#             */
/*   Updated: 2021/12/20 16:15:14 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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
	spec->txt_lst = txt_lst_new(NO_TXT);
	config_to_spec(head->next, spec, 0);
	free_config(head);
}
