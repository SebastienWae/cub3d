# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 13:49:18 by swaegene          #+#    #+#              #
#    Updated: 2022/06/12 10:03:16 by swaegene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

RM = rm -rf
MKDIR = mkdir -p

LIBFT = libft
SRC_DIR = src
OUT_DIR = out
DEBUG_DIR = debug

CC = clang
WARNING = -Wall -Wextra -Werror
CFLAGS = -O3
CPPFLAGS = -I$(LIBFT) -Isrc
LDFLAGS = -L$(LIBFT) -lft -lm
CPPFLAGS += -I/usr/local/include
LDFLAGS += -L/usr/local/lib -lmlx

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
	graphics/raycaster.c \
	graphics/raycaster_utils.c \
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
SRCS_BONUS = $(SRCS:config/parser.c=config/parser_bonus.c)
SRCS_PATH = $(addprefix $(SRC_DIR)/,$(SRCS))
SRCS_PATH_BONUS = $(addprefix $(SRC_DIR)/,$(SRCS_BONUS))
OBJS = $(addprefix $(OUT_DIR)/,$(SRCS_PATH:%.c=%.o))
OBJS_BONUS = $(addprefix $(OUT_DIR)/,$(SRCS_PATH_BONUS:%.c=%.o))
OBJS_DEBUG = $(addprefix $(DEBUG_DIR)/,$(SRCS_PATH:%.c=%.o))
OBJS_BONUS_DEBUG = $(addprefix $(DEBUG_DIR)/,$(SRCS_PATH_BONUS:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) CC=$(CC) -C $(LIBFT) bonus

$(OUT_DIR)/%.o: %.c
	$(MKDIR) $(@D)
	$(COMPILE.c) $< $(WARNING) -MMD -MP -o $@

$(DEBUG_DIR)/%.o: %.c
	$(MKDIR) $(@D)
	$(COMPILE.c) $< $(WARNING) -MMD -MP -o $@

.PHONY: bonus
bonus: $(OBJS_BONUS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LDFLAGS) -o $(NAME)

.PHONY: debug debug_clean debug_fclean debug_re
debug: CFLAGS = -g3 -fsanitize=address -fno-omit-frame-pointer \
	-fno-optimize-sibling-calls
debug: WARNING = -Wall -Wextra
debug: $(OBJS_DEBUG) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS_DEBUG) $(LDFLAGS) -o $(NAME)_debug
debug_bonus: CFLAGS = -g3 -fsanitize=address -fno-omit-frame-pointer \
	-fno-optimize-sibling-calls
debug_bonus: WARNING = -Wall -Wextra
debug_bonus: $(OBJS_BONUS_DEBUG) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS_BONUS_DEBUG) $(LDFLAGS) -o $(NAME)_debug
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
