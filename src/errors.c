/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:42:24 by seb               #+#    #+#             */
/*   Updated: 2022/05/29 12:47:49 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <errno.h>
#include <errors.h>
#include <stdlib.h>

void	error_exit(char *msg)
{
	error_msg();
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(EXIT_FAILURE);
}

void	error_msg(void)
{
	ft_putstr_fd("Error\n", 2);
	if (errno > 0) // FIXME: false positive?
		perror(NULL);
}
