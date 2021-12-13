/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:53:41 by ghan              #+#    #+#             */
/*   Updated: 2021/12/13 15:39:59 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isint(char *str)
{
	int	k;

	k = -1;
	if (is_charset(str[0], "+-"))
		k++;
	while (str[++k])
		if (!ft_isdigit(str[k]))
			return (0);
	return (1);
}
