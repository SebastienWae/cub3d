/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:05:19 by seb               #+#    #+#             */
/*   Updated: 2022/06/11 16:13:03 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/game.h>
#include <utils/errors.h>

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc == 1)
		error_msg("Missing path to the config file", ADD);
	else if (argc == 2)
	{
		game = game_init(argv[1]);
		if (game)
		{
			game_start_loop(game);
			game_destructor(game);
		}
	}
	else
		error_msg("Too many arguments", ADD);
	error_msg(NULL, FLUSH);
}
