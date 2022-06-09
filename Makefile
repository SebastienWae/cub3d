# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 13:49:18 by swaegene          #+#    #+#              #
#    Updated: 2022/06/09 13:47:32 by jeulliot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

RM = rm -rf
MKDIR = mkdir -p
UNAME_S := $(shell uname -s)

LIBFT = libft
SRC_DIR = src
OUT_DIR = out
DEBUG_DIR = debug

CC = clang
 WARNING = -Wall -Wextra -Werror
CFLAGS = -O3
CPPFLAGS = -I$(LIBFT) -Isrc
LDFLAGS = -L$(LIBFT) -lft -lm
ifeq ($(UNAME_S),Linux)
	CPPFLAGS += -Iminilibx_linux
	LDFLAGS += -Lminilibx_linux -lmlx -lXext -lX11
	MINILIBX = minilibx_linux
endif
ifeq ($(UNAME_S),Darwin)
	# CPPFLAGS += -I/usr/local/include
	CPPFLAGS += -Iminilibx_darwin
	# LDFLAGS += -L/usr/local/lib  -lmlx -framework OpenGL -framework AppKit -lz
	LDFLAGS +=  -Lminilibx_darwin  -lmlx -framework OpenGL -framework AppKit -lz
	MINILIBX = minilibx_darwin
endif

SRCS = main.c \
	utils/errors.c \
	utils/get_next_line.c \
	utils/utils.c \
	config/config.c \
	config/color.c \
	config/texture.c \
	config/map.c \
	config/parser.c \
	config/parser_map.c \
	graphics/window.c \
	graphics/image.c \
	graphics/draw.c \
	graphics/raycaster.c \
	graphics/minimap.c \
	graphics/render.c \
	graphics/walls.c \
	graphics/color.c \
	game/door.c \
	game/game.c \
	game/player.c \
	game/loop.c \
	game/move.c \
	game/rotate.c
SRCS_PATH = $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS = $(addprefix $(OUT_DIR)/,$(SRCS_PATH:%.c=%.o))
OBJS_DEBUG = $(addprefix $(DEBUG_DIR)/,$(SRCS_PATH:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/libft.a $(MINILIBX)/libmlx.a
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) CC=$(CC) -C $(LIBFT) bonus

$(MINILIBX)/libmlx.a:
	$(MAKE) CC=$(CC) -C $(MINILIBX)

$(OUT_DIR)/%.o: %.c
	$(MKDIR) $(@D)
	$(COMPILE.c) $< $(WARNING) -MMD -MP -o $@

$(DEBUG_DIR)/%.o: %.c
	$(MKDIR) $(@D)
	$(COMPILE.c) $< $(WARNING) -MMD -MP -o $@

.PHONY: bonus
bonus: $(NAME)

.PHONY: debug debug_clean debug_fclean debug_re
debug: CFLAGS = -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
debug: $(OBJS_DEBUG) $(LIBFT)/libft.a $(MINILIBX)/libmlx.a
	$(CC) $(CFLAGS) $(OBJS_DEBUG) $(LDFLAGS) -o $(NAME)_debug
debug_clean:
	$(RM) $(DEBUG_DIR)
debug_fclean: debug_clean
	$(RM) $(NAME)_debug
debug_re: debug_fclean debug

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
