/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:28:42 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/02 13:57:14 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <game/game.h>
#include <config/config.h>
#include <config/parser.h>
#include <utils/strings.h>

static void	map_append(t_config *config, char *line, int i)
{
	size_t	len;
	char	**map;
	int		n;

	len = ft_strlen(line) - 2;
	line[len + 1] = 0;
	map = malloc(sizeof(char *) * (i + 1));
	if (!map)
		return ;
	n = 0;
	while (n < i)
	{
		map[n] = config->map[n];
		n++;
	}
	map[n] = ft_strdup(line);
	free(config->map);
	config->map = map;
	if (len > config->map_max_width)
		config->map_max_width = len;
	config->map_height++;
}

t_parser_state	map_handler(t_game *game, char *line, int *i)
{
	if (is_empty(line) || ft_strlen(line) < 1)
	{
		if (!game->config->map)
			return (CP_S_MAP);
		else
			return (CP_S_ERROR);
	}
	else if (*i >= 6)
	{
		map_append(game->config, line, *i - 6);
		(*i)++;
		if (game->config->map)
			return (CP_S_MAP);
		else
			return (CP_S_ERROR);
	}
	else
		return (CP_S_ERROR);
}

void	map_get_scale(t_game *game)
{
	size_t	height;
	size_t	width;

	width = WINDOW_WIDTH / game->config->map_max_width;
	height = WINDOW_HEIGHT / game->config->map_height;
	if (width > height)
		game->config->scale = height / 4;
	else
		game->config->scale = width / 4;
	if (game->config->scale % 2 == 0)
		game->config->scale = game->config->scale + 1;
}
