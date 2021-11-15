/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:12:42 by ghan              #+#    #+#             */
/*   Updated: 2021/11/15 16:34:21 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_config_details(int fd, t_conf *cur)
{
	char	**elem_info;
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '\0')
		{
			elem_info = ft_split(line, ' ');
			cur->elem = elem_info[0];
		}
		free(line);
	}
}

void	check_config(int argc, char **argv)
{
	int		fd;
	t_conf	head;

	if (argc != 2)
		is_error("miniRT must display only one scene!", NULL, EXIT_FAILURE);
	else if (!argv[1] || ft_strlen(argv[1]) < 4
		|| ft_strcmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt"))
		is_error("Invalid .rt file", NULL, EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		is_error("Open failed: ", strerror(errno), EXIT_FAILURE);
	head.next = NULL;
	check_config_details(fd, head.next);
	close(fd);
}