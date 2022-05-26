/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:07:27 by seb               #+#    #+#             */
/*   Updated: 2022/05/26 22:09:41 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config.h>

t_config	*config_constructor(char *config_file_path)
{
	(void)config_file_path;
	return (0);
}

void	config_destructor(t_config *config)
{
	(void)config;
}
