#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2017/03/11 17:48:43 by mcanal           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	corewar
ASM =	asm

NAME_MAIN =	corewar_main.c
ASM_MAIN =	asm_main.c

C_UTIL =	error.c

C_NAME =

C_ASM =
C_PARSER =	asm_parser.c

O_DIR = obj
VPATH =	src/util:src/asm:src/asm/parser:src/corewar

N_OBJS =	$(NAME_MAIN:%.c=$(O_DIR)/%.o)	\
			$(C_NAME:%.c=$(O_DIR)/%.o)		\
			$(C_UTIL:%.c=$(O_DIR)/%.o)

A_OBJS =	$(ASM_MAIN:%.c=$(O_DIR)/%.o)	\
			$(C_ASM:%.c=$(O_DIR)/%.o)		\
			$(C_UTIL:%.c=$(O_DIR)/%.o)		\
			$(C_PARSER:%.c=$(O_DIR)/%.o)

DEPS =		$(N_OBJS:%.o=%.d)	$(A_OBJS:%.o=%.d)

RM =		rm -rf
MKDIR =		mkdir -p
MAKE =		make -j
ECHO =      echo -e
CC =		$(shell clang --version >/dev/null 2>&1 && echo clang || echo gcc)

CFLAGS =	-Wall -Wextra -Werror -O2
LIBFT_DIR =	libft
LIBFT	 =	$(LIBFT_DIR)/libft.a
N_LIBS = 	$(LIBFT)
A_LIBS =	$(LIBFT)
I_DIR =		-I$(LIBFT_DIR)/inc/ -Iinc/

WHITE =		\033[37;01m
RED =		\033[31;01m
GREEN =		\033[32;01m
YELLOW =	\033[33;01m
BLUE =		\033[34;01m
BASIC =		\033[0m

.PHONY: all debug sanitize me_cry clean fclean zclean re brute

all:
	@$(MAKE) -C $(LIBFT_DIR) $(FLAGS)
	@$(MAKE) $(NAME) $(FLAGS)
	@$(MAKE) $(ASM) $(FLAGS)

debug: FLAGS = "CFLAGS = -g -ggdb"
debug: all

sanitize: FLAGS = "CFLAGS = -g -ggdb -fsanitize=address,undefined -ferror-limit=5"
sanitize: all

me_cry: FLAGS = "CFLAGS = -Wpedantic -Wshadow -Wconversion -Wcast-align \
-Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
-Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
-Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
-Wredundant-decls -Wall -Werror -Wextra" #-Wcast-qual
me_cry: all

-include $(DEPS)

$(NAME): $(N_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(I_DIR) $(N_OBJS) $(N_LIBS) -o $@
	@$(ECHO) "$(BLUE)$(N_OBJS) $(N_LIBS) $(WHITE)->$(RED) $@ $(BASIC)"
	@$(ECHO) "$(WHITE)flags:$(BASIC) $(CFLAGS)"
	@$(ECHO) "$(WHITE)compi:$(BASIC) $(CC)"

$(ASM): $(A_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(I_DIR) $(A_OBJS) $(A_LIBS) -o $@
	@$(ECHO) "$(BLUE)$(A_OBJS) $(A_LIBS) $(WHITE)->$(RED) $@ $(BASIC)"
	@$(ECHO) "$(WHITE)flags:$(BASIC) $(CFLAGS)"
	@$(ECHO) "$(WHITE)compi:$(BASIC) $(CC)"

$(O_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(I_DIR) -MMD -c $< -o $@
	@$(ECHO) "$(WHITE)$<\t->$(BLUE) $@ $(BASIC)"

$(N_OBJS): | $(O_DIR)
$(A_OBJS): | $(O_DIR)

$(O_DIR):
	@$(MKDIR) $(O_DIR)

clean:
	@$(RM) $(O_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(ASM)

mrproper: fclean
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
