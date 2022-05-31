/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:05:19 by seb               #+#    #+#             */
/*   Updated: 2022/05/31 12:06:44 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/game.h>
#include <utils/errors.h>

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc == 1)
		error_exit("Missing path to the config file");
	else if (argc == 2)
	{
		game = game_init(argv[1]);
		if (!game)
			exit(EXIT_FAILURE);
		game_start_loop(game);
		game_destructor(game);
	}
	else
		error_exit("Too many arguments");
}
