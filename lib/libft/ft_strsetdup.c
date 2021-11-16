/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsetdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:42:25 by ghan              #+#    #+#             */
/*   Updated: 2021/11/16 15:27:08 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsetdup(char **src)
{
	char	**ret;
	int		i;

	if (!src)
		return (NULL);
	ret = (char **)ft_calloc(ft_strsetlen(src) + 1, sizeof(char *));
	i = -1;
	while (src[++i])
		ret[i] = ft_strdup(src[i]);
	return (ret);
}
