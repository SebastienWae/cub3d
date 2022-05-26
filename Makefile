# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seb <seb@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 13:49:18 by swaegene          #+#    #+#              #
#    Updated: 2022/05/23 14:49:45 by seb              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

RM = rm -rf
MKDIR = mkdir -p

LIBFT = libft
SRC_DIR = src
OUT_DIR = out

CC = gcc
CFLAGS += -Wall -Wextra -Werror
CPPFLAGS = -I$(LIBFT) -Iinclude
LDFLAGS = -L$(LIBFT) -lft

SRCS = main.c
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS = $(addprefix $(OUT_DIR)/,$(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

.PHONY = debug debug_clean debug_fclean debug_re
debu%: CFLAGS += -g3 -fsanitize=address
debug:
	$(MAKE) CFLAGS="$(CFLAGS)" OUT_DIR=debug NAME=$(NAME)_debug
debug_clean:
	$(MAKE) CFLAGS="$(CFLAGS)" OUT_DIR=debug NAME=$(NAME)_debug clean
debug_fclean:
	$(MAKE) CFLAGS="$(CFLAGS)" OUT_DIR=debug NAME=$(NAME)_debug fclean
debug_re:
	$(MAKE) CFLAGS="$(CFLAGS)" OUT_DIR=debug NAME=$(NAME)_debug re

.PHONY = bonus
bonus: $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT) bonus

$(OUT_DIR)/%.o: %.c
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY = clean
clean: 
	$(RM) $(OUT_DIR)
	$(MAKE) -C $(LIBFT) clean

.PHONY = fclean
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) fclean

.PHONY = re
re: fclean all

.PHONY = cc
cc: $(LIBFT)/libft.a
	bear -- make re

.PHONY = check_cc
check_cc: cc
	codechecker analyze compile_commands.json -o .cc
	codechecker parse .cc

.PHONY = check_infer
check_infer: re
	infer run -- make re

.PHONY = check_gcc
check_gcc: CFLAGS = -fanalyzer
check_gcc:
	$(MAKE) CFLAGS=$(CFLAGS) OUT_DIR=check NAME=$(NAME)_check
	$(RM) check
	$(RM) $(NAME)_check
