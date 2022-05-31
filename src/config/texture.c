/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:01:20 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/31 11:15:11 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <game/game.h>
#include <config/parser.h>
#include <utils/strings.h>

static void	*texture_constructor(char *line, t_game *game)
{
	char	*path;
	void	*img;
	int		width;
	int		height;

	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	path = ft_strtrim(line + 2, " \n");
	img = mlx_xpm_file_to_image(game->window->mlx, path, &width, &height);
	free(path);
	return (img);
}

t_parser_state	texture_handler(t_game *game, char *line, int *i)
{
	int			t_index;
	static char	*identifiers[4] = {"NO ", "SO ", "WE ", "EA "};

	t_index = *i;
	if (is_empty(line))
		return (CP_S_TEXTURES);
	else if (t_index >= 0 && t_index <= 4)
	{
		(*i)++;
		if (ft_strncmp(identifiers[t_index], line, 3) == 0)
		{
			game->config->textures[t_index] = texture_constructor(line, game);
			if (!game->config->textures[t_index])
				return (CP_S_ERROR);
			if (t_index == 3)
				return (CP_S_COLORS);
			return (CP_S_TEXTURES);
		}
		else
			return (CP_S_ERROR);
	}
	else
		return (CP_S_ERROR);
}
