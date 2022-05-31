/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:28:42 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/31 11:16:22 by seb              ###   ########.fr       */
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
