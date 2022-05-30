# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 13:49:18 by swaegene          #+#    #+#              #
#    Updated: 2022/05/30 15:23:24 by swaegene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

RM = rm -rf
MKDIR = mkdir -p
UNAME_S := $(shell uname -s)

LIBFT = libft
SRC_DIR = src
OUT_DIR = out

CC = gcc
CFLAGS += -Wall -Wextra -Werror
CPPFLAGS = -I$(LIBFT) -Isrc
LDFLAGS = -L$(LIBFT) -lft
ifeq ($(UNAME_S),Linux)
	CPPFLAGS += -Iminilibx_linux
	LDFLAGS += -Lminilibx_linux -lmlx -lXext -lX11
endif
ifeq ($(UNAME_S),Darwin)
	CPPFLAGS += -Iminilibx_darwin
	LDFLAGS += -Lminilibx_darwin -lmlx -framework OpenGL -framework AppKit -lz
endif

SRCS = main.c errors.c \
	strings/get_next_line.c \
	strings/utils.c \
	config/config.c \
	config/color.c \
	config/texture.c \
	config/map.c \
	config/map_check.c \
	graphics/window.c \
	graphics/image.c
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS = $(addprefix $(OUT_DIR)/,$(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

.PHONY: debug debug_clean debug_fclean debug_re
debu%: CFLAGS += -g3 -fsanitize=address
debug:
	$(MAKE) CFLAGS="$(CFLAGS)" OUT_DIR=debug NAME=$(NAME)_debug
debug_clean:
	$(MAKE) CFLAGS="$(CFLAGS)" OUT_DIR=debug NAME=$(NAME)_debug clean
debug_fclean:
	$(MAKE) CFLAGS="$(CFLAGS)" OUT_DIR=debug NAME=$(NAME)_debug fclean
debug_re:
	$(MAKE) CFLAGS="$(CFLAGS)" OUT_DIR=debug NAME=$(NAME)_debug re

.PHONY: bonus
bonus: $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT) bonus

$(OUT_DIR)/%.o: %.c
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean: 
	$(RM) $(OUT_DIR)
	$(MAKE) -C $(LIBFT) clean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) fclean

.PHONY: re
re: fclean all

.PHONY: cc
cc: $(LIBFT)/libft.a
	bear -- make re

.PHONY: check_cc
check_cc: cc
	codechecker analyze compile_commands.json -o .cc
	codechecker parse .cc

.PHONY: check_infer
check_infer: re
	infer run -- make re

.PHONY: check_gcc
check_gcc: CFLAGS = -fanalyzer
check_gcc:
	$(MAKE) CFLAGS=$(CFLAGS) OUT_DIR=check NAME=$(NAME)_check
	$(RM) check
	$(RM) $(NAME)_check
