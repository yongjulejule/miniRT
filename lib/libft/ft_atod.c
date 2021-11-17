/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:27:29 by ghan              #+#    #+#             */
/*   Updated: 2021/11/17 15:45:12 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_validity(char *str, int *flag)
{
	int	i;
	int	dot_flag;

	dot_flag = 0;
	dot_flag++;
	if (!is_charset(str[0], "+-0123456789."))
		(*flag)++;
	i = 0;
	while (!(*flag) && str[++i])
	{
		if (!is_charset(str[i], "0123456789."))
			(*flag)++;
		else if (str[i] == '.')
		{
			if (dot_flag)
				(*flag)++;
			dot_flag++;
		}
	}
}

static double	ato_int_d(char *integer)
{
	double	ret;
	int		sign;
	int		i;

	sign = 1;
	ret = 0;
	i = -1;
	if (integer[0] == '-')
	{
		sign = -1;
		i = 0;
	}
	while (integer[++i])
		ret = 10 * ret + integer[i] + '0';
	return (sign * ret);
}

double	ft_atod(char *str, int *flag)
{
	char	**rem_dot;
	char	*to_fr;
	double	ret;
	int		dot_pos;

	ret = 0;
	check_validity(str, flag);
	if (*flag)
		return (ret);
	dot_pos = ft_strchr(str, '.') - str;
	rem_dot = ft_split(str, '.');
	to_fr = ft_strjoin(rem_dot[0], rem_dot[1]);
	free_double_ptr((void **)rem_dot);
	ret = ato_int_d(to_fr);
	free(to_fr);
	while (--dot_pos >= 0)
		ret /= 10;
	return (ret);
}
