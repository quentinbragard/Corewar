/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:51:39 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/12 14:03:47 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int			add_instruction(t_info *info, t_ins *ins)
{
	int i;

	i = 0;
	if ((ins->op_code = operation_recon(info)) < 0)
		return (-1);
	if (!args_counter(info, ins))
		return (ft_usage(8, info));
	if (args_recon(info, ins) == -1)
		return (-1);
	return (0);
}

int			instructions_init(t_info *info, t_ins *ins)
{
	int	i;

	i = -1;
	if ((i = skip_blanks(info)) < 0)
		return (-1);
	if (!*(info->file))
		return (1);
	while (is_banned(info->file[i], 5, ' ', '\t', LABEL_CHAR
				, COMMENT_CHAR, ALT_COMMENT_CHAR)
			&& i < ft_pos('\n', info->file))
		i++;
	if (is_authorized(info->file[i], 2, ' ', '\t'))
		return (add_instruction(info, ins));
	if (info->file[i] == LABEL_CHAR)
		return (add_label(info, ins));
	else
		return (ft_usage(6, info));
}

static void	update_sizes_bis(t_info *info, t_ins *ins, int size, int two)
{
	if (ins->arg_3[0] == T_REG)
		size += T_REG_SIZE;
	else if (ins->arg_3[0] == T_DIR || ins->arg_3[0] == T_LAB)
		size += T_IND_SIZE + two;
	else if (ins->arg_3[0] == T_IND || ins->arg_3[0] == T_IND_LAB)
		size += T_IND_SIZE;
	ins->instruc_size = size;
	info->current_pos += size;
}

void		update_sizes(t_info *info, t_ins *ins)
{
	int size;
	int	one;
	int	two;

	one = ins->op_code == 1 || ins->op_code == 9 || ins->op_code == 12
		|| ins->op_code == 15 ? 0 : 1;
	two = ins->op_code <= 8 || ins->op_code == 13 || ins->op_code == 16 ? 2 : 0;
	size = OP_SIZE + one;
	if (ins->arg_1[0] == T_REG)
		size += T_REG_SIZE;
	else if (ins->arg_1[0] == T_DIR || ins->arg_1[0] == T_LAB)
		size += T_IND_SIZE + two;
	else if (ins->arg_1[0] == T_IND || ins->arg_1[0] == T_IND_LAB)
		size += T_IND_SIZE;
	if (ins->arg_2[0] == T_REG)
		size += T_REG_SIZE;
	else if (ins->arg_2[0] == T_DIR || ins->arg_2[0] == T_LAB)
		size += T_IND_SIZE + two;
	else if (ins->arg_2[0] == T_IND || ins->arg_2[0] == T_IND_LAB)
		size += T_IND_SIZE;
	update_sizes_bis(info, ins, size, two);
}

int			get_instruction_list(t_info *info, t_ins *ins)
{
	t_ins	*tmp;

	tmp = ins;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ins_malloc_initialization(info);
	ins = tmp->next;
	return (instructions_init(info, ins));
}
