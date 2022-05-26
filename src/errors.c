/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:42:24 by seb               #+#    #+#             */
/*   Updated: 2022/05/26 22:52:03 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <errors.h>

void	error_exit(t_err_type err_type)
{
	static char	*err_msg[] = {
		"Too many arguments.",
		"Missing arguments."
	};

	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err_msg[err_type], 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("usage: cub3d <path/to_the_map/file.cub>\n", 2);
	exit(1);
}
