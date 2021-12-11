/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commas_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:50:39 by ghan              #+#    #+#             */
/*   Updated: 2021/12/11 11:28:33 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

char	**check_commas_split(char *vect)
{
	int	i;
	int	cnt;

	if (!vect)
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	if (vect[0] == ',' || vect[ft_strlen(vect) - 1] == ',')
		is_error("Invalid configuration", NULL, EXIT_FAILURE);
	i = 0;
	cnt = 0;
	while (vect[i])
	{
		if (vect[i] == ',')
		{
			cnt++;
			if (cnt > 1)
				is_error("Invalid configuration", NULL, EXIT_FAILURE);
		}
		else
			cnt = 0;
		i++;
	}
	return (ft_split(vect, ','));
}
