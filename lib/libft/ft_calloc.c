/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:18:23 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/16 11:31:55 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*str;
	size_t			idx;

	idx = 0;
	str = (unsigned char *)malloc(sizeof(unsigned char) * size * count);
	if (str == 0)
	{
		ft_putendl_fd("Error\nFailed to allocate", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (idx < count * size)
	{
		*(str + idx) = 0;
		idx++;
	}
	return (str);
}
