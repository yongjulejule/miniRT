/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:27:29 by ghan              #+#    #+#             */
/*   Updated: 2021/12/07 14:19:53 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_validity(char *str, int *flag)
{
	int	i;
	int	dot_flag;

	dot_flag = 0;
	if (!ft_strcmp(str, "+") || !ft_strcmp(str, "-")
		|| !ft_strcmp(str, ".") || !ft_strcmp(str, "+.")
		|| !ft_strcmp(str, "-."))
		(*flag)++;
	else if (!is_charset(str[0], "+-0123456789."))
		(*flag)++;
	i = 0;
	while (str[++i] && !(*flag))
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
	if (integer[0] == '-' || integer[0] == '+')
	{
		i = 0;
		if (integer[0] == '-')
			sign = -1;
	}
	while (integer[++i])
		ret = 10 * ret + integer[i] - '0';
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
	dot_pos = ft_strlen(str) + str - ft_strchr(str, '.');
	rem_dot = ft_split(str, '.');
	to_fr = ft_strjoin(rem_dot[0], rem_dot[1]);
	free_double_ptr((void **)rem_dot);
	ret = ato_int_d(to_fr);
	free(to_fr);
	while (ft_strchr(str, '.') && --dot_pos > 0)
		ret /= 10;
	return (ret);
}
