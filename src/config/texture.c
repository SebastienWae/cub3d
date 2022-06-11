/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:01:20 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/11 15:38:57 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <game/game.h>
#include <config/parser.h>
#include <config/texture.h>
#include <utils/strings.h>
#include <utils/errors.h>
#include <utils/bool.h>
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

t_bool	texture_handler(char *line, t_game *game)
{
	int			id;
	static char	*txt_ids[4] = {"NO ", "SO ", "WE ", "EA "};

	id = is_in_array(txt_ids, 4, line);
	if (id >= 0)
	{
		if (game->config->walls_txt[id])
			return (FALSE);
		game->config->walls_txt[id] = texture_constructor(line, game);
		if (!game->config->walls_txt[id])
			return (FALSE);
		return (TRUE);
	}
	else
		return (FALSE);
}
