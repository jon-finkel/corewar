/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 20:43:23 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/24 15:13:27 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "asm_parser.h"

#ifdef ANNOYING_DEBUG
static void			debug_type(t_arg_type type)
{
	fprintf(stderr, DEBUG_HEADER "<type");
	if (type & T_REG)
		fprintf(stderr, ": T_REG");
	if (type & T_DIR)
		fprintf(stderr, ": T_DIR");
	if (type & T_IND)
		fprintf(stderr, ": T_IND");
	if (type & T_LAB)
		fprintf(stderr, ": T_LAB");
	fprintf(stderr, ">\n");
}
#endif	/* DEBUG */

static t_byte		parse_arg_length(t_arg_type arg_type, int direct_size)
{
	if (arg_type & T_REG)
		return (sizeof(t_byte));
	else if (arg_type & T_IND)
		return (sizeof(t_word));
	else if (arg_type & T_DIR)
		return (direct_size ? sizeof(t_word) : sizeof(t_dword));

	return (0);
}

static t_arg_type	parse_arg_type(char *arg)
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
		return (T_LAB | ret);
	if (*arg == '-' && ft_isdigit(*(arg + 1)))
		arg++;
	while (*arg)
		if (!ft_isdigit(*arg++))
			error(E_INVALID, "Invalid arg (not a number).");
	return (ret);
}

void				parse_args(t_instruct_read *instruct_r, \
							t_instruct_parsed *instruct_p)
{
	int	i;

	if ((t_byte)instruct_r->argc != instruct_p->op->param_nb)
		error(E_INVALID, "Invalid arg (wrong number).");
	if (!instruct_r->argc)
		return ;

	i = 0;
	while (i < instruct_r->argc)
	{
		*(instruct_p->arg_type + i) = parse_arg_type(*(instruct_r->argv + i));

		*(instruct_p->arg_length + i) = \
			parse_arg_length(*(instruct_p->arg_type + i), \
							instruct_p->op->direct_size);

#ifdef ANNOYING_DEBUG
		debug_type(*(instruct_p->arg_type + i));
#endif	/* DEBUG */

		if ((!(*(instruct_p->arg_type + i) & ~T_LAB)) \
				& *(instruct_p->op->param_type + i))
			error(E_INVALID, "Invalid arg (wrong arg type).");

		i++;
	}
}
