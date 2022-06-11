/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:19:23 by seb               #+#    #+#             */
/*   Updated: 2022/06/11 16:42:05 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <game/game.h>
#include <config/parser.h>
#include <config/color.h>
#include <config/texture.h>
#include <config/config.h>
#include <config/map.h>
#include <utils/strings.h>
#include <utils/errors.h>
#include <utils/bool.h>
#include <utils/vec.h>

t_bool	parse_config_line(char *line, t_game *game)
{
	t_bool	result;

	result = FALSE;
	if (game->config->colors[FLOOR] && game->config->colors[CEILING]
		&& game->config->walls_txt[NORTH] && game->config->walls_txt[SOUTH]
		&& game->config->walls_txt[WEST] && game->config->walls_txt[EAST])
	{
		if (map_handler(game, line))
			result = TRUE;
	}
	else
	{
		if (is_empty(line))
			result = TRUE;
		else
		{
			if (texture_handler(line, game))
				result = TRUE;
			if (!result && color_handler(line, game))
				result = TRUE;
		}
	}
	return (result);
}

t_bool	parse_config_file(int fd, t_game *game)
{
	int		config_index;
	char	*line;

	config_index = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (parse_config_line(line, game))
		{
			free(line);
			line = get_next_line(fd);
		}
		else
		{
			error_msg("Config file error at line: ", ADD_NO_NL);
			error_msg(ft_itoa(config_index + 1), ADD);
			if (line[0] != '\n')
				error_msg(line, ADD_NO_NL);
			free(line);
			return (FALSE);
		}
		config_index++;
	}
	return (TRUE);
}

t_bool	parse_map_handlers(t_game *game, size_t c[2], t_bool s[2])
{
	char	curr;

	curr = game->config->map[c[HEIGHT]][c[WIDTH]];
	if (game->config->map_height - 1 == c[HEIGHT]
		&& ((curr != ' ' && curr != '1') || !game->player))
		return (FALSE);
	if (curr == ' ')
		return (map_space_handler(game, c, s));
	else if (curr == '1')
	{
		s[IN_WALL] = TRUE;
		return (TRUE);
	}
	else if (curr == '0')
		return (map_zero_handler(game, c, s));
	else if (curr == 'N' || curr == 'S' || curr == 'W' || curr == 'E')
		return (map_player_handler(game, c, s));
	else if (curr == 'D')
		return (map_door_handler(game, c, s));
	else
		return (FALSE);
}

t_bool	parse_map(t_game *game)
{
	size_t	i[2];
	t_bool	state[2];

	map_normalize(game);
	i[HEIGHT] = 0;
	state[PLAYER] = FALSE;
	while (i[HEIGHT] < game->config->map_height)
	{
		i[WIDTH] = 0;
		state[IN_WALL] = FALSE;
		while (i[WIDTH] < game->config->map_width)
		{
			if (!parse_map_handlers(game, i, state))
			{
				error_msg("Map error at line: ", ADD_NO_NL);
				error_msg(ft_itoa(i[HEIGHT] + 1), ADD_NO_NL);
				error_msg(" col: ", ADD_NO_NL);
				error_msg(ft_itoa(i[WIDTH] + 1), ADD);
				return (FALSE);
			}
			i[WIDTH]++;
		}
		i[HEIGHT]++;
	}
	return (TRUE);
}

void	parse_player(t_game *game, size_t c[2])
{
	game->player = player_constructor();
	game->player->position = (t_vec)
	{
		.x = (int)(c[WIDTH] * 64 + 32),
		.y = (int)(c[HEIGHT] * 64 + 32)
	};
	if (game->config->map[c[HEIGHT]][c[WIDTH]] == 'N')
		game->player->direction = M_PI_2;
	if (game->config->map[c[HEIGHT]][c[WIDTH]] == 'E')
		game->player->direction = 0;
	if (game->config->map[c[HEIGHT]][c[WIDTH]] == 'W')
		game->player->direction = M_PI;
	if (game->config->map[c[HEIGHT]][c[WIDTH]] == 'S')
		game->player->direction = 3 * M_PI / 2;
	game->player->delta = (t_vec)
	{
		.x = cos(game->player->direction),
		.y = -sin(game->player->direction)
	};
}
