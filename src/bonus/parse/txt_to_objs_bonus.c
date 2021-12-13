/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_to_objs_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:01:52 by ghan              #+#    #+#             */
/*   Updated: 2021/12/13 23:24:44 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	read_ppm(int fd, t_txt_lst *cur)
{
	char	*line;
	int		n;

	n = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0 || (line && *line != '\0'))
	{
		if (line && *line != '\0')
		{
			if (n == 0 && ft_strcmp(line, "P3"))
				is_error("Invalid ppm format", NULL, EXIT_FAILURE);
			else if (n == 1)
				trail_n_cons_del_split(line, ' ');
			else if (n == 2)

			else
		}
		free(line);
		line = NULL;
		n++;
	}
	if (line)
		free(line);
}

static void	ppm_to_struct(t_txt_lst *cur, int *o_t_flag,
				int type, unsigned int n_obj)
{
	static int		obj_idx;
	int				fd;
	char			*tmp;
	unsigned int	i;

	if (cur->obj_flag[0] > n_obj)
		is_error("Invalid configuration (OBJ IDX)", NULL, EXIT_FAILURE);
	i = 0;
	while (i < cur->obj_flag[0])
	{
		if (cur->obj_flag[i] >= n_obj)
			is_error("Invalid configuration (OBJ IDX)", NULL, EXIT_FAILURE);
		o_t_flag[cur->obj_flag[i]] = obj_idx;
		i++;
	}
	if (type == CHECKERED)
		fd = open("./etc/texture/check.ppm", O_RDONLY);
	else
	{
		tmp = ft_strjoin("./etc/texture/", cur->f_name);
		fd = open(tmp, O_RDONLY);
		free(tmp);
	}
	if (fd < 0)
		is_error("ppm file open failed", NULL, EXIT_FAILURE);
	read_ppm(fd, cur);
	close(fd);
}

void	txt_to_objs(t_spec *spec, unsigned int n_obj)
{
	t_txt_lst	*cur;

	spec->txt.obj_txt_flag = (int *)ft_calloc(n_obj, sizeof(int));
	cur = spec->txt.txt_lst->next;
	while (cur)
	{
		if (cur->type == CHECKERED)
			ppm_to_struct(cur, spec->txt.obj_txt_flag, CHECKERED, n_obj);
		cur = cur->next;
	}

}
