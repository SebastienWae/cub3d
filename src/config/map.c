/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:28:42 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/30 17:20:59 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/map.h>
#include <utils/bool.h>
#include <config/config.h>
#include <libft.h>
#include <stddef.h>
#include <utils/strings.h>

static t_bool	config_map_check_char(t_config *conf, size_t c[2], t_bool s[2])
{
	char	curr;

	curr = conf->map[c[HEIGHT]][c[WIDTH]];
	if (curr == ' ')
		return (map_space_handler(conf, c, s));
	else if (curr == '1')
	{
		s[IN_WALL] = TRUE;
		return (TRUE);
	}
	else if (curr == '0')
		return (map_zero_handler(conf, c, s));
	else if (curr == 'N' || curr == 'S' || curr == 'W' || curr == 'E')
		return (map_player_handler(conf, c, s));
	else if (curr == 'D')
		return (map_door_handler(conf, c, s));
	else
		return (FALSE);
}

t_bool	config_map_is_valid(t_config *config)
{
	size_t	i[2];
	t_bool	state[2];

	i[HEIGHT] = 0;
	state[PLAYER] = FALSE;
	while (i[HEIGHT] < config->map_height)
	{
		i[WIDTH] = 0;
		state[IN_WALL] = FALSE;
		while (i[WIDTH] < ft_strlen(config->map[i[HEIGHT]]))
		{
			if (!config_map_check_char(config, i, state))
				return (FALSE);
			i[WIDTH]++;
		}
		i[HEIGHT]++;
	}
	if (!state[PLAYER])
		return (FALSE);
	return (TRUE);
}

static void	config_map_append(t_config *config, char *line, int i)
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

t_parser_state	config_handle_map(t_config *config, char *line, int *i)
{
	if (is_empty(line) || ft_strlen(line) < 1)
	{
		if (!config->map)
			return (CP_S_MAP);
		else
			return (CP_S_ERROR);
	}
	else if (*i >= 6)
	{
		config_map_append(config, line, *i - 6);
		(*i)++;
		if (config->map)
			return (CP_S_MAP);
		else
			return (CP_S_ERROR);
	}
	else
		return (CP_S_ERROR);
}
