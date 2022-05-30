/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:12:21 by seb               #+#    #+#             */
/*   Updated: 2022/05/30 17:19:49 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

# define BUFFER_SIZE 1000

# include <utils/bool.h>

int		array_size(void **array);
char	*get_next_line(int fd);
t_bool	is_empty(char *str);

#endif
