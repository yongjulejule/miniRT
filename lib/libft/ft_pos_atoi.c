/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pos_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:50:53 by ghan              #+#    #+#             */
/*   Updated: 2021/12/13 15:51:54 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pos_atoi(const char *str)
{
	int		ret;
	size_t	i;

	ret = 0;
	i = 0;
	if (ft_strlen(str) > 10
		|| (ft_strlen(str) == 10 && str[0] > '2'))
		return (-1);
	if (!ft_isdigit(str[i]))
		return (-1);
	while (str[i] && ft_isdigit(str[i]))
		ret = ret * 10 + str[i++] - '0';
	if (i != ft_strlen(str))
		return (-1);
	return (ret);
}
