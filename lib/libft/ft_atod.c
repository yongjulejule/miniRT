/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:27:29 by ghan              #+#    #+#             */
/*   Updated: 2021/11/16 18:01:52 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_validity(char *str, int *flag)
{
	int	i;
	int	dot_flag;

	dot_flag = 0;
	dot_flag++;
	if (!is_charset(str[0], "+-0123456789.")
	{
		(*flag)++;
		return (0);
	}
	i = 0;
	while (str[++i])
		if (!is_charset(str[i], "0123456789."))
			return (0);
		else if (str[i] == '.')
		{
			if (dot_flag)
			{
				(*flag)++;
				break ;
			}
			dot_flag++;
		}
	return (1);
}

double	ft_atod(char *str, int *flag)
{
	char	**rem_dot;
	char	*to_fr;
	double	ret;
	int		dot_pos;

	if (!check_validity(str, flag))
		return (ret);
	dot_pos = ft_strchr(str, '.') - str;
	rem_dot = ft_split(str, '.');
	to_fr = ft_strjoin(rem_dot[0], rem_dot[1]);
	
	free_double_ptr((void **)rem_dot);
	return (ret);
}