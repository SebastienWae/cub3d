/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:37:02 by seb               #+#    #+#             */
/*   Updated: 2022/06/09 15:44:24 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <game/game.h>
#include <config/parser.h>
#include <utils/bool.h>

/*
return false when:
- in contact with something else than a space or a wall
*/
t_bool	map_space_handler(t_game *game, size_t c[2], t_bool s[2])
{
	s[IN_WALL] = FALSE;
	if (c[HEIGHT] > 0
		&& game->config->map[c[HEIGHT] - 1][c[WIDTH]] != ' '
		&& game->config->map[c[HEIGHT] - 1][c[WIDTH]] != '1')
		return (FALSE);
	else if (c[HEIGHT] < game->config->map_height - 1
		&& game->config->map[c[HEIGHT] + 1][c[WIDTH]] != ' '
		&& game->config->map[c[HEIGHT] + 1][c[WIDTH]] != '1')
		return (FALSE);
	else if (c[WIDTH] > 0
		&& game->config->map[c[HEIGHT]][c[WIDTH] - 1] != ' '
		&& game->config->map[c[HEIGHT]][c[WIDTH] - 1] != '1')
		return (FALSE);
	else if (c[WIDTH] < ft_strlen(game->config->map[c[HEIGHT]]) - 1
		&& game->config->map[c[HEIGHT]][c[WIDTH] + 1] != ' '
		&& game->config->map[c[HEIGHT]][c[WIDTH] + 1] != '1')
		return (FALSE);
	else
		return (TRUE);
}

/*
return false when:
- on the first/last row or column
- not in wall
- next to nothing
- next to space
*/
t_bool	map_zero_handler(t_game *game, size_t c[2], t_bool s[2])
{
	if (c[HEIGHT] == 0
		|| c[WIDTH] == 0
		|| c[HEIGHT] == game->config->map_height - 1
		|| c[WIDTH] == ft_strlen(game->config->map[c[HEIGHT]]) - 1)
		return (FALSE);
	else if (!s[IN_WALL])
		return (FALSE);
	else if (c[WIDTH] > ft_strlen(game->config->map[c[HEIGHT] - 1]) - 1
		|| game->config->map[c[HEIGHT] - 1][c[WIDTH]] == ' '
		|| c[WIDTH] > ft_strlen(game->config->map[c[HEIGHT] + 1]) - 1
		|| game->config->map[c[HEIGHT] + 1][c[WIDTH]] == ' ')
		return (FALSE);
	return (TRUE);
}

/*
return false when:
- on the first/last row or column
- not in wall
- player is already set
- next to nothing
- next to space
*/
t_bool	map_player_handler(t_game *game, size_t c[2], t_bool s[2])
{	
	if (s[PLAYER])
		return (FALSE);
	else
		s[PLAYER] = TRUE;
	if (c[HEIGHT] == 0
		|| c[WIDTH] == 0
		|| c[HEIGHT] == game->config->map_height - 1
		|| c[WIDTH] == ft_strlen(game->config->map[c[HEIGHT]]) - 1)
		return (FALSE);
	else if (!s[IN_WALL])
		return (FALSE);
	else if (c[WIDTH] > ft_strlen(game->config->map[c[HEIGHT] - 1]) - 1
		|| game->config->map[c[HEIGHT] - 1][c[WIDTH]] == ' '
		|| c[WIDTH] > ft_strlen(game->config->map[c[HEIGHT] + 1]) - 1
		|| game->config->map[c[HEIGHT] + 1][c[WIDTH]] == ' ')
		return (FALSE);
	parse_player(game, c);
	return (TRUE);
}

/*
return false when:
- on the first/last row or column
- not in wall
- next to nothing
- next to space
*/
// TODO: set door in game struct
t_bool	map_door_handler(t_game *game, size_t c[2], t_bool s[2])
{
	if (c[HEIGHT] == 0
		|| c[WIDTH] == 0
		|| c[HEIGHT] == game->config->map_height - 1
		|| c[WIDTH] == ft_strlen(game->config->map[c[HEIGHT]]) - 1)
		return (FALSE);
	else if (!s[IN_WALL])
		return (FALSE);
	else if (c[WIDTH] > ft_strlen(game->config->map[c[HEIGHT] - 1]) - 1
		|| game->config->map[c[HEIGHT] - 1][c[WIDTH]] == ' '
		|| c[WIDTH] > ft_strlen(game->config->map[c[HEIGHT] + 1]) - 1
		|| game->config->map[c[HEIGHT] + 1][c[WIDTH]] == ' ')
		return (FALSE);
	return (TRUE);
}
