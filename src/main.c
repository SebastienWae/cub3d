/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:05:19 by seb               #+#    #+#             */
/*   Updated: 2022/05/26 22:07:04 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config.h>

int	main(int argc, char **argv)
{
	t_config	*config;

	if (argc == 2)
	{
		config = config_constructor(argv[1]);
		config_destructor(config);
	}
}
