/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:19:23 by seb               #+#    #+#             */
/*   Updated: 2022/05/31 21:18:07 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <math.h>
#include <game/game.h>
#include <config/parser.h>
#include <config/color.h>
#include <config/texture.h>
#include <config/map.h>
#include <utils/strings.h>
#include <utils/errors.h>
#include <utils/bool.h>

// TODO: print after basic error msg
static void	config_error(char *line)
{
	ft_putstr_fd("Config file error at line: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
}

t_bool	parse_config_file(int fd, t_game *game)
{
	int				config_index;
	t_parser_state	state;
	char			*line;

	config_index = 0;
	state = CP_S_TEXTURES;
	line = get_next_line(fd);
	while (line && state != CP_S_DONE)
	{
		if (state == CP_S_TEXTURES)
			state = texture_handler(game, line, &config_index);
		else if (state == CP_S_COLORS)
			state = color_handler(game, line, &config_index);
		else
			state = map_handler(game, line, &config_index);
		if (state == CP_S_ERROR)
		{
			config_error(line);
			free(line);
			return (FALSE);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (TRUE);
}

static t_bool	parse_map_handlers(t_game *game, size_t c[2], t_bool s[2])
{
	char	curr;

	curr = game->config->map[c[HEIGHT]][c[WIDTH]];
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
	size_t	len;
	size_t	i[2];
	t_bool	state[2];

	i[HEIGHT] = 0;
	state[PLAYER] = FALSE;
	while (i[HEIGHT] < game->config->map_height)
	{
		i[WIDTH] = 0;
		state[IN_WALL] = FALSE;
		len = ft_strlen(game->config->map[i[HEIGHT]]);
		while (i[WIDTH] < len)
		{
			if (!parse_map_handlers(game, i, state))
				return (FALSE);
			i[WIDTH]++;
		}
		i[HEIGHT]++;
	}
	return (TRUE);
}

void	parse_player(t_game *game, size_t c[2])
{
	size_t	size;

	if (WINDOW_WIDTH / game->config->map_max_width
		> WINDOW_HEIGHT / game->config->map_height)
		size = WINDOW_HEIGHT / game->config->map_height / 4;
	else
		size = WINDOW_WIDTH / game->config->map_max_width / 4;
	if (size % 2 == 0)
		size = size + 1;
	game->player->x = c[WIDTH] * size + size / 2;
	game->player->y = c[HEIGHT] * size + size / 2;
	if (game->config->map[c[HEIGHT]][c[WIDTH]] == 'N')
		game->player->direction = M_PI_2;
	if (game->config->map[c[HEIGHT]][c[WIDTH]] == 'E')
		game->player->direction = 0;
	if (game->config->map[c[HEIGHT]][c[WIDTH]] == 'W')
		game->player->direction = M_PI;
	if (game->config->map[c[HEIGHT]][c[WIDTH]] == 'S')
		game->player->direction = 3 * M_PI_2;
}
