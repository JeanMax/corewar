/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:24:52 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/13 01:03:49 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** parse content (except header) of the .s files
*/

#include "asm_parser.h"

// <--- DEBUG
t_instruct	instruct = { {0}, NULL, {{0}}, {0} };

static void				debug_instruct()
{
	t_uint i;

	ft_debugstr("label", instruct.label);
	if (instruct.op)
	{
		ft_debugstr("op", instruct.op->name);
		i = 0;
		while (i < instruct.op->arg_count)
		{
			ft_debugstr("arg", *(instruct.arg + i));
			if (*(instruct.arg_type + i) & T_REG)
				ft_debugstr("type", "T_REG");
			if (*(instruct.arg_type + i) & T_DIR)
				ft_debugstr("type", "T_DIR");
			if (*(instruct.arg_type + i) & T_IND)
				ft_debugstr("type", "T_IND");
			if (*(instruct.arg_type + i) & T_LAB)
				ft_debugstr("type", "T_LAB");
			i++;
		}
	}
	ft_putendl("");
}
// DEBUG --->

static t_arg_type		check_arg_type(char *arg)
{
	int			i;
	t_arg_type	ret;

	ret = T_IND;
	if (*arg == 'r')
	{
		i = ft_atoi(++arg);
		if (i < 1 || i > REG_NUMBER)
			error(E_INVALID, "Invalid register (REG_NUMBER not in range).");
		ret = T_REG;
	}
	else if (*arg == DIRECT_CHAR && ++arg)
		ret = T_DIR;

	if (*arg == LABEL_CHAR && ret != T_REG)
		return (T_LAB | ret); //TODO: check if label exists, eventually after...
	while (*arg)
		if (!ft_isdigit(*arg++))
			error(E_INVALID, "Invalid arg (not a number).");
	return (ret);
}

static enum e_progress	parse_arg(char *arg, size_t len)
{
	char	*arg_start;
	char	*arg_swap;
	t_uint	arg_count;

	arg_count = 0;
	arg_swap = arg;
	while ((size_t)(arg_swap - arg) < len)
	{
		arg_start = arg_swap;
		while ((size_t)(arg_swap - arg) < len && *arg_swap != SEPARATOR_CHAR)
			arg_swap++;

		ft_memcpy(instruct.arg + arg_count, arg_start,	\
				  (size_t)(arg_swap - arg_start));
		*(*(instruct.arg + arg_count) + (size_t)(arg_swap - arg_start)) = 0;
		*(instruct.arg_type + arg_count) = \
			check_arg_type(*(instruct.arg + arg_count));

		if (*arg_swap == SEPARATOR_CHAR)
			arg_swap++;
		arg_count++;
	}

	if (arg_count != instruct.op->arg_count)
		error(E_INVALID, "Invalid arg (wrong number).");
	return (P_ARG);
}

static enum e_progress	parse_op(char *op, size_t len)
{
	t_op	*op_tab_swap;

	op_tab_swap = op_tab;
	while (op_tab_swap->name && ft_memcmp(op_tab_swap->name, op, len))
		op_tab_swap++;
	if (!op_tab_swap->name)
		error(E_INVALID, "Invalid op (not found).");
	instruct.op = op_tab_swap;

	return (P_OP);
}

static enum e_progress	parse_label(char *label, size_t len)
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

static enum e_progress	parse_instruction(char *line, enum e_progress progress)
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
		progress |= parse_label(word_start, (size_t)(line - word_start - 1));
	}
	else if (!(progress & P_OP))
		progress |= parse_op(word_start, (size_t)(line - word_start));
	else
		progress |= parse_arg(word_start, (size_t)(line - word_start));

	return (parse_instruction(line, progress));
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

	progress = parse_instruction(line, P_NOPROGRESS);
	if (!(!progress //nothing found
		  || (progress & P_LABEL && !(progress & P_OP)) //just a label
		  || (progress & P_OP && progress & P_ARG))) //(label +) op + arg
		error(E_INVALID, "Something's wrong with that instruction.");

	if (progress)
		debug_instruct();			/* DEBUG */
	ft_bzero(&instruct, sizeof(t_instruct));

	ft_memdel((void **)&line);
	read_loop(fd);
}
