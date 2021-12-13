/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trail_cons_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:50:39 by ghan              #+#    #+#             */
/*   Updated: 2021/12/13 22:38:02 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

char	**trail_n_cons_del_split(char *str, char delimiter)
{
	int	i;
	int	cnt;

	if (!str)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	if (str[0] == delimiter || str[ft_strlen(str) - 1] == delimiter)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == delimiter)
		{
			cnt++;
			if (cnt > 1)
				is_error("Invalid configuration", NULL, EXIT_FAILURE);
		}
		else
			cnt = 0;
		i++;
	}
	return (ft_split(str, delimiter));
}
