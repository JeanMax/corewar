/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/13 14:09:32 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_PARSER_H

# define ASM_PARSER_H

# include "asm.h"

# include "op.h"

/*
** open
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
** read / close
*/
# include <unistd.h>

# define IS_EOL(c) (!c || c == COMMENT_CHAR)
# define MAX_ARG_LENGTH		31
# define MAX_LABEL_LENGTH	23


/*
** parsing progress enum
*/
enum					e_progress
{
	P_NOPROGRESS = 0,
	P_LABEL = (1 << 0),
	P_OP = (1 << 1),
	P_ARG = (1 << 2),
};

/*
** instruction struct
** TODO: error: padding size of 'struct s_instruct' with 4 bytes to alignment boundary
*/
typedef struct		s_instruct
{
	char				label[MAX_LABEL_LENGTH + 1];
	t_op				*op;
	char				arg[MAX_ARGS_NUMBER][MAX_ARG_LENGTH + 1];
	t_arg_type			arg_type[MAX_ARGS_NUMBER];
}					t_instruct;

/*
** parse_header.c
*/
void					read_header(int fd, char *cmd_string);

/*
** parse_instruction.c
*/
void					read_loop(int fd);

#endif
