/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:05:19 by seb               #+#    #+#             */
/*   Updated: 2022/05/26 22:36:19 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <config.h>
#include <errors.h>

int	main(int argc, char **argv)
{
	t_config	*config;

	if (argc == 1)
		ft_putstr_fd(ERR_MISSING_ARGS, 2);
	else if (argc == 2)
	{
		config = config_constructor(argv[1]);
		config_destructor(config);
	}
	else
		ft_putstr_fd(ERR_TOO_MANY_ARGS, 2);
}
