/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:01:20 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/11 14:06:46 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <game/game.h>
#include <config/parser.h>
#include <config/texture.h>
#include <utils/strings.h>
#include <utils/errors.h>
#include <graphics/image.h>

t_bool	texture_open_images(t_game *g)
{
	g->config->doors_txt[DOOR_OPEN]
		= texture_constructor(DOOR_OPEN_TEXTURE, g);
	g->config->doors_txt[DOOR_CLOSE]
		= texture_constructor(DOOR_CLOSE_TEXTURE, g);
	g->config->player_txt
		= texture_constructor(PLAYER_MINIMAP_TEXTURE, g);
	if (g->config->doors_txt[DOOR_OPEN] && g->config->doors_txt[DOOR_CLOSE]
		&& g->config->player_txt)
		return (TRUE);
	error_msg("Error loading assets", ADD);
	return (FALSE);
}

static void	*texture_img_ft(t_game *g, char *p, int len, t_texture *t)
{
	if (len >= 4 && !ft_strncmp(p + (len - 4), ".xpm", 5))
		return (mlx_xpm_file_to_image(g->window->mlx,
				p,
				&(t->width),
				&(t->height)));
	else if (len >= 4 && !ft_strncmp(p + (len - 4), ".png", 5))
		return (mlx_png_file_to_image(g->window->mlx,
				p,
				&(t->width),
				&(t->height)));
	else
	{
		error_msg("Texture error: '", ADD_NO_NL);
		error_msg(p, ADD_NO_NL);
		error_msg("' file type is not supported", ADD);
		return (NULL);
	}
}

static t_bool	texture_img(t_game *g, char *p, int len, t_texture *t)
{
	t_image		*image;
	void		*img;

	img = texture_img_ft(g, p, len, t);
	free(p);
	if (img)
	{
		image = image_constructor(g->window, img);
		if (!img)
		{
			error_msg("Memory error: texture_img", ADD);
			return (FALSE);
		}
		t->img = image;
		return (TRUE);
	}
	return (FALSE);
}

void	*texture_constructor(char *line, t_game *game)
{
	t_texture	*texture;
	char		*path;
	int			len;

	texture = ft_calloc(1, sizeof(t_texture));
	if (!texture)
	{
		error_msg("Memory error: texture_constructor", ADD);
		return (NULL);
	}
	path = ft_strtrim(line + 2, " \n");
	len = ft_strlen(path);
	if (texture_img(game, path, len, texture))
		return (texture);
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
			game->config->walls_txt[t_index] = texture_constructor(line, game);
			if (!game->config->walls_txt[t_index])
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
