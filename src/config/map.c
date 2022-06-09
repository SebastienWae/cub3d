/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:28:42 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/09 20:49:55 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <math.h>
#include <game/game.h>
#include <config/config.h>
#include <config/parser.h>
#include <utils/strings.h>
#include <utils/errors.h>

void	map_normalize(t_game *game)
{
	int		y;
	int		len;
	char	*new_line;

	y = 0;
	while (game->config->map[y])
	{
		len = ft_strlen(game->config->map[y]);
		if (len < game->config->map_width)
		{
			new_line = ft_calloc(game->config->map_width + 1, sizeof(char));
			if (!new_line)
				return ;
			ft_memcpy(new_line, game->config->map, len);
			ft_memset(new_line + len, ' ', game->config->map_width - len);
		}
	}
}

static void	map_append(t_config *config, char *line, int i)
{
	size_t	len;
	char	**map;
	int		n;

	len = ft_strlen(line);
	line[len - 1] = 0;
	map = ft_calloc(i + 1, sizeof(char *));
	if (!map)
	{
		error_msg("Memory error: map_append", ADD);
		return ;
	}
	n = 0;
	while (n < i)
	{
		map[n] = config->map[n];
		n++;
	}
	map[n] = ft_strdup(line);
	free(config->map);
	config->map = map;
	if (len > config->map_width)
		config->map_width = len;
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
