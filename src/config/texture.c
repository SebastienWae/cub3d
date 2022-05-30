/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:01:20 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/30 17:20:44 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/config.h>
#include <libft.h>
#include <utils/strings.h>
#include <graphics/window.h>

static void	*texture_constructor(char *line, t_window *window)
{
	char	*path;
	void	*img;
	int		width;
	int		height;

	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	path = ft_strtrim(line + 2, " \n");
	img = mlx_xpm_file_to_image(window->mlx, path, &width, &height);
	free(path);
	return (img);
}

t_parser_state	config_handle_texture(t_config *conf, char *line, int *i,
		t_window *window)
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
			conf->textures[t_index] = texture_constructor(line, window);
			if (!conf->textures[t_index])
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
