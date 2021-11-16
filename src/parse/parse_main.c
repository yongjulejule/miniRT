/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:12:42 by ghan              #+#    #+#             */
/*   Updated: 2021/11/16 16:13:23 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_double_ptr(void **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
	}
	free(ptr);
	ptr = NULL;
}

static void	read_config(int fd, t_conf **hd)
{
	char	**elem_info;
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '\0')
		{
			elem_info = ft_split(line, ' ');
			conf_lst_addback(hd, conf_lst_new(ft_strdup(elem_info[0]),
					ft_strsetdup(elem_info + 1)));
			free_double_ptr((void **)elem_info);
		}
		free(line);
		line = NULL;
	}
}

void	check_config(int argc, char **argv, t_spec *spec)
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
	config_to_spec(head, spec);
}
