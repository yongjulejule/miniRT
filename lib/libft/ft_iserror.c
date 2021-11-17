/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iserror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:35:29 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/17 16:18:11 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	is_error(char *err_msg, char *sys_err, int exit_status)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (err_msg != NULL)
		ft_putstr_fd(err_msg, STDERR_FILENO);
	if (sys_err != NULL)
		ft_putstr_fd(sys_err, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	exit(exit_status);
}
