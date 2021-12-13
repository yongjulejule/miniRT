/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fill_ppm_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:43:59 by ghan              #+#    #+#             */
/*   Updated: 2021/12/14 02:02:06 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	fill_ppm_size(t_txt_lst *cur, char *line)
{
	char	**size_str;

	size_str = trail_n_cons_del_split(line, ' ');
	if (ft_strsetlen(size_str) != 2)
		is_error("Invalid ppm format (SIZE)", NULL, EXIT_FAILURE);
	cur->ppm.size[X] = ft_pos_atoi(size_str[X]);
	cur->ppm.size[Y] = ft_pos_atoi(size_str[Y]);
	if (cur->ppm.size[X] < 0 || cur->ppm.size[Y] < 0)
		is_error("Invalid ppm format (SIZE)", NULL, EXIT_FAILURE);
	cur->ppm.color_arr = (int *)ft_calloc(cur->ppm.size[X]
			* cur->ppm.size[Y] * 3, sizeof(int));
}

static void	fill_ppm_color_arr(t_txt_lst *cur, char *line, int n)
{
	char	**color_arr_str;
	int		i;
	int		k;

	if (n >= cur->ppm.size[Y])
		is_error("Invalid ppm format (TOO LONG)", NULL, EXIT_FAILURE);
	color_arr_str = trail_n_cons_del_split(line, ' ');
	i = 0;
	while (i < cur->ppm.size[X])
	{
		// FIXME - HEAP BUFFER OVERFLOW
		k = n * cur->ppm.size[Y] + i;
		cur->ppm.color_arr[k] = ft_pos_atoi(color_arr_str[i]);
		if (cur->ppm.color_arr[k] < 0 || cur->ppm.color_arr[k] > 255)
			is_error("Invalid ppm format (EXCEED COLOR RANGE)",
				NULL, EXIT_FAILURE);
		i++;
	}
	free(color_arr_str);
}

void	read_fill_ppm(int fd, t_txt_lst *cur)
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
				fill_ppm_size(cur, line);
			else if (n == 2 && ft_strcmp(line, "255"))
				is_error("Invalid ppm format (MAX NO)", NULL, EXIT_FAILURE);
			else
				fill_ppm_color_arr(cur, line, n - 3);
		}
		free(line);
		line = NULL;
		n++;
	}
	if (line)
		free(line);
}
