/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:28:42 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/11 15:55:14 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <game/game.h>
#include <config/parser.h>
#include <utils/strings.h>
#include <utils/errors.h>

void	map_normalize(t_game *game)
{
	int		y;
	int		len;
	char	*nl;
	char	*tmp;

	y = 0;
	while (y < game->config->map_height && game->config->map[y])
	{
		len = ft_strlen(game->config->map[y]);
		if (len < game->config->map_width)
		{
			nl = ft_calloc(game->config->map_width + 1, sizeof(char));
			if (!nl)
				return ;
			ft_strlcpy(nl, game->config->map[y], len + 1);
			ft_memset(nl + len, ' ', game->config->map_width - len);
			nl[(int)game->config->map_width] = 0;
			tmp = game->config->map[y];
			game->config->map[y] = nl;
			free(tmp);
		}
		y++;
	}
}

static void	map_append(t_config *config, char *line, int i)
{
	size_t	len;
	char	**map;
	int		n;

	len = ft_strlen(line) - 1;
	line[len] = 0;
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

t_bool	map_handler(t_game *game, char *line)
{
	static int	map_h;

	if (is_empty(line) || ft_strlen(line) < 1)
	{
		if (!game->config->map)
			return (TRUE);
		else
			return (FALSE);
	}
	else
	{
		map_append(game->config, line, map_h);
		map_h++;
		if (game->config->map)
			return (TRUE);
		else
			return (FALSE);
	}
}
