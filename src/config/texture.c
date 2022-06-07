/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:01:20 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/07 19:54:21 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics/image.h"
#include <stdlib.h>
#include <libft.h>
#include <mlx.h>
#include <game/game.h>
#include <config/parser.h>
#include <config/texture.h>
#include <graphics/window.h>
#include <utils/strings.h>

// TODO: error handling

static void	*texture_constructor(char *line, t_game *game)
{
	t_texture	*texture;
	t_image		*image;
	char		*path;
	void		*img;
	int			len;

	texture = ft_calloc(1, sizeof(t_texture));
	if (!texture)
		return (NULL);
	path = ft_strtrim(line + 2, " \n");
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (!ft_strncmp(path + (len - 4), ".xpm", 5))
		img = mlx_xpm_file_to_image(game->window->mlx, path,
				&(texture->width), &(texture->height));
#ifdef __APPLE__
	else if (!ft_strncmp(path + (len - 4), ".png", 5))
		img = mlx_png_file_to_image(game->window->mlx, path,
				&(texture->width), &(texture->height));
#endif
	else
		return (0);
	free(path);
	if (img)
	{
		image = image_constructor(game->window, img);
		if (!img)
			return (NULL);
		texture->img = image;
		return (texture);
	}
	else
	{
		free(texture);
		return (NULL);
	}
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
