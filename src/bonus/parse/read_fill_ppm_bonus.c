/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fill_ppm_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:43:59 by ghan              #+#    #+#             */
/*   Updated: 2021/12/14 17:31:07 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	fill_ppm_size(t_txt_lst *cur, char *line)
{
	char	**size_str;

	size_str = ft_split(line, ' ');
	if (ft_strsetlen(size_str) != 2)
		is_error("Invalid ppm format (SIZE)", NULL, EXIT_FAILURE);
	cur->ppm.size[X] = ft_pos_atoi(size_str[X]);
	cur->ppm.size[Y] = ft_pos_atoi(size_str[Y]);
	if (cur->ppm.size[X] < 0 || cur->ppm.size[Y] < 0)
		is_error("Invalid ppm format (SIZE)", NULL, EXIT_FAILURE);
	cur->ppm.color_arr = (int *)ft_calloc(cur->ppm.size[X]
			* cur->ppm.size[Y] * 3, sizeof(int));
	free_double_ptr((void **)size_str);
}

static void	fill_ppm_color_arr(t_txt_lst *cur, char *line, int *n, int *k)
{
	char	**color_arr_str;
	int		i;

	if (*n >= cur->ppm.size[Y] + 3)
		is_error("Invalid ppm format (TOO LONG)", NULL, EXIT_FAILURE);
	color_arr_str = ft_split(line, ' ');
	i = 0;
	while (color_arr_str[i] && i < cur->ppm.size[X] * 3)
	{
		cur->ppm.color_arr[*k] = ft_pos_atoi(color_arr_str[i]);
		if (cur->ppm.color_arr[*k] < 0 || cur->ppm.color_arr[*k] > 255)
			is_error("Invalid ppm format (EXCEED COLOR RANGE)",
				NULL, EXIT_FAILURE);
		i++;
		(*k)++;
		if ((*k) == (*n) * cur->ppm.size[X] * 3)
			(*n)++;
	}
	free_double_ptr((void **)color_arr_str);
}

void	read_fill_ppm(int fd, t_txt_lst *cur, int n, int k)
{
	char	*line;

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
			else if (n > 2)
				fill_ppm_color_arr(cur, line, &n, &k);
			if (n == 0 || n == 1 || n == 2)
				n++;
		}
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
}
