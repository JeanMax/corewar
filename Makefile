#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2017/03/19 20:53:57 by mcanal           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	corewar
ASM =	asm

C_UTIL =	error.c op.c

C_NAME =	corewar_main.c

C_ASM =		asm_main.c		init_data.c
C_LEXER =	asm_lexer.c		read_header.c	read_instruction.c
C_PARSER =	asm_parser.c	parse_args.c
C_ENCODER = asm_encoder.c

TEST = test.sh

T_DIR = ./test
O_DIR = obj
VPATH =	src/util:src/asm:src/asm/lexer:src/asm/parser:src/asm/encoder:src/corewar

N_OBJS =	$(C_NAME:%.c=$(O_DIR)/%.o)		\
			$(C_UTIL:%.c=$(O_DIR)/%.o)

A_OBJS =	$(C_ASM:%.c=$(O_DIR)/%.o)		\
			$(C_UTIL:%.c=$(O_DIR)/%.o)		\
			$(C_PARSER:%.c=$(O_DIR)/%.o)	\
			$(C_LEXER:%.c=$(O_DIR)/%.o)		\
			$(C_ENCODER:%.c=$(O_DIR)/%.o)

DEPS =		$(N_OBJS:%.o=%.d)	$(A_OBJS:%.o=%.d)

RM =		rm -rf
MKDIR =		mkdir -p
MAKE =		make
MAKEFLAGS =	-j 4
ECHO =		echo -e
CC =		$(shell clang --version &>/dev/null && echo clang || echo gcc)
UNAME_S =   $(shell uname -s)

PREV_FLAGS_LOG = .previous-flag
PREV_FLAGS = "$(shell cat "$(O_DIR)/$(PREV_FLAGS_LOG)" 2>/dev/null)"

ifeq ($(UNAME_S), Linux)
  ECHO = echo -e
else ifeq ($(UNAME_S), Darwin)
  ECHO = echo
endif

CFLAGS =	-Wall -Wextra -Werror -O2
LIBFT_DIR =	libft
LIBFT =		$(LIBFT_DIR)/libft.a
N_LIBS =	$(LIBFT)
A_LIBS =	$(LIBFT)
I_DIR =		-I$(LIBFT_DIR)/inc/ -Iinc/

WHITE =		\033[37;01m
RED =		\033[31;01m
GREEN =		\033[32;01m
YELLOW =	\033[33;01m
BLUE =		\033[34;01m
BASIC =		\033[0m

ifndef VERBOSE
.SILENT:
endif

.PHONY: all debug sanitize me_cry  re clean fclean mrproper  test

all: | $(O_DIR)
ifeq (,$(findstring fsanitize, $(PREV_FLAGS)))
	test $(PREV_FLAGS) && $(ECHO) $(FLAGS) | grep -q fsanitize && $(MAKE) mrproper && $(MKDIR) $(O_DIR) || true
else
	test $(PREV_FLAGS) && $(ECHO) $(FLAGS) | grep -qv fsanitize && $(MAKE) mrproper && $(MKDIR) $(O_DIR) || true
endif
	$(ECHO) $(FLAGS) > $(O_DIR)/$(PREV_FLAGS_LOG)

	$(MAKE) -C $(LIBFT_DIR) $(FLAGS)
	$(MAKE) $(NAME) $(FLAGS)
	$(MAKE) $(ASM) $(FLAGS)

debug: FLAGS = "CFLAGS = -g -ggdb"
debug: all

sanitize: FLAGS = "CFLAGS = -g -ggdb -fsanitize=address,undefined -ferror-limit=5"
sanitize: all

me_cry: FLAGS = "CFLAGS = -Wpedantic -Wshadow -Wconversion -Wcast-align \
-Wstrict-prÂototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
-Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
-Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
-Wredundant-decls -Wall -Werror -Wextra" #-Wcast-qual
me_cry: all

re: fclean all

-include $(DEPS)

$(NAME): $(N_OBJS) $(LIBFT)
	@$(ECHO) "$(BLUE)$(N_OBJS) $(N_LIBS) $(WHITE)->$(RED) $@ $(BASIC)"
	$(CC) $(CFLAGS) $(I_DIR) $(N_OBJS) $(N_LIBS) -o $@
	@$(ECHO) "$(WHITE)flags:$(BASIC) $(CFLAGS)"
	@$(ECHO) "$(WHITE)compi:$(BASIC) $(CC)"

$(ASM): $(A_OBJS) $(LIBFT)
	@$(ECHO) "$(BLUE)$(A_OBJS) $(A_LIBS) $(WHITE)->$(RED) $@ $(BASIC)"
	$(CC) $(CFLAGS) $(I_DIR) $(A_OBJS) $(A_LIBS) -o $@
	@$(ECHO) "$(WHITE)flags:$(BASIC) $(CFLAGS)"
	@$(ECHO) "$(WHITE)compi:$(BASIC) $(CC)"

$(O_DIR)/%.o: %.c
	@$(ECHO) "$(WHITE)$<\t->$(BLUE) $@ $(BASIC)"
	$(CC) $(CFLAGS) $(I_DIR) -MMD -c $< -o $@

$(O_DIR):
	$(MKDIR) $(O_DIR)

clean:
	$(RM) $(O_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(ASM)

mrproper: fclean
	$(MAKE) -C $(LIBFT_DIR) fclean


test: all
	$(T_DIR)/$(TEST)
