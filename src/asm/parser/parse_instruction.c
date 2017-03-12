/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:24:52 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/12 21:47:49 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** parse content (except header) of the .s files
*/

#include "asm_parser.h"

static enum e_progress	parse_arg(char *arg, size_t len)
{
	char	arg_todo[len + 1]; //TODO

	//TODO: check that the number of args match op
	//TODO: check syntax
	ft_memcpy(arg_todo, arg, len);
	*(arg_todo + len) = 0;

	ft_debugstr("arg", arg_todo); /* DEBUG */
	return (P_ARG);
}

static enum e_progress	parse_op(char *op, size_t len)
{
	char	op_todo[len + 1]; //TODO

	//TODO: check that op exists in op.c
	//TODO: store somewhere the number of args
	ft_memcpy(op_todo, op, len);
	*(op_todo + len) = 0;

	ft_debugstr("op", op_todo); /* DEBUG */
	return (P_OP);
}

static enum e_progress	parse_label(char *label, size_t len)
{
	char	label_todo[len + 1]; //TODO
	char	*label_swap;

	label_swap = label;
	while ((size_t)(label_swap - label) < len)
		if (!ft_strchr(LABEL_CHARS, *label_swap++))
			error(E_INVALID, "Invalid label (forbidden character).");

	ft_memcpy(label_todo, label, len);
	*(label_todo + len) = 0;

	ft_debugstr("label", label_todo); /* DEBUG */
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

	ft_memdel((void **)&line);
	read_loop(fd);
}
