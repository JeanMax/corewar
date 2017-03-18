/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:24:52 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/18 00:54:23 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** read content (except header) of the .s files
*/

#include "asm_lexer.h"

// <--- DEBUG
t_instruct_read	instruct = { {0}, {0}, 0, {{0}} };

static void				debug_instruct()
{
	ft_debugstr("label", instruct.label);
	ft_debugstr("op", instruct.op);
	ft_debugnbr("argc", instruct.argc);

	for (int i = 0; i < instruct.argc; i++)
		ft_debugstr("argv", instruct.argv[i]);
	ft_putendl("");
}
// DEBUG --->


static enum e_progress	read_arg(char *arg, size_t len)
{
	char	*arg_start;
	char	*arg_swap;
	int		arg_count;

	arg_count = 0;
	arg_swap = arg;
	while ((size_t)(arg_swap - arg) < len && arg_count < MAX_ARGS_NUMBER)
	{
		arg_start = arg_swap;
		while ((size_t)(arg_swap - arg) < len && *arg_swap != SEPARATOR_CHAR)
			arg_swap++;

		if ((size_t)(arg_swap - arg_start) > MAX_ARG_LENGTH)
			error(E_INVALID, "Invalid arg (too long).");
		ft_memcpy(instruct.argv + arg_count, arg_start,	\
				  (size_t)(arg_swap - arg_start));
		*(*(instruct.argv + arg_count) + (size_t)(arg_swap - arg_start)) = 0;

		if (*arg_swap == SEPARATOR_CHAR)
			arg_swap++;
		arg_count++;
	}
	if (arg_count > MAX_ARGS_NUMBER)
		error(E_INVALID, "Invalid arg (too many).");

	instruct.argc = arg_count;
	return (P_ARG);
}

static enum e_progress	read_op(char *op, size_t len)
{
	if (len > MAX_OP_CODE_LENGTH)
		error(E_INVALID, "Invalid op (too long).");
	ft_memcpy(&instruct.op, op, len);
	*(instruct.op + len) = 0;

	return (P_OP);
}

static enum e_progress	read_label(char *label, size_t len)
{
	char	*label_swap;

	label_swap = label;
	while ((size_t)(label_swap - label) < len)
		if (!ft_strchr(LABEL_CHARS, *label_swap++))
			error(E_INVALID, "Invalid label (forbidden character).");

	if (len > MAX_LABEL_LENGTH)
		error(E_INVALID, "Invalid label (too long).");
	ft_memcpy(&instruct.label, label, len);
	*(instruct.label + len) = 0;

	return (P_LABEL);
}

static enum e_progress	read_instruction(char *line, enum e_progress progress)
{
	char		*word_start;

	while (!IS_EOL(*line) && ft_isspace(*line))
		line++;
	if (IS_EOL(*line))
		return (progress);
	word_start = line;
	while (!IS_EOL(*line) && !ft_isspace(*line))
		line++;

	if (*(line - 1) == LABEL_CHAR)
	{
		if (progress & P_LABEL || progress & P_OP)
			error(E_INVALID, "Invalid label (label/op already found).");
		progress |= read_label(word_start, (size_t)(line - word_start - 1));
	}
	else if (!(progress & P_OP))
		progress |= read_op(word_start, (size_t)(line - word_start));
	else
		progress |= read_arg(word_start, (size_t)(line - word_start));

	return (read_instruction(line, progress));
}

void					read_loop(int fd)
{
	int				ret;
	char			*line;
	enum e_progress	progress;

	line = NULL;
	if (!(ret = get_next_line(fd, &line)))
		return ;
	else if (ret == -1)
		error(E_READ, NULL);

	progress = read_instruction(line, P_NOPROGRESS);
	if (!(!progress //nothing found
		  || (progress & P_LABEL && !(progress & P_OP)) //just a label
		  || (progress & P_OP && progress & P_ARG))) //(label +) op + arg
		error(E_INVALID, "Something's wrong with that instruction.");

	if (progress)
		debug_instruct();			/* DEBUG */
	ft_bzero(&instruct, sizeof(t_instruct_read));

	ft_memdel((void **)&line);
	read_loop(fd);
}
