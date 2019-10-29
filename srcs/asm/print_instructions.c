/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzimmerm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:25:47 by lzimmerm          #+#    #+#             */
/*   Updated: 2019/09/12 13:58:47 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void	print_instructions_bis(t_info *info, t_ins *ins)
{
	if (ins->arg_2[0] == T_REG)
		reg_writing(info, ins->arg_2);
	else if (ins->arg_2[0] == T_DIR)
		dir_writing(info, ins->arg_2, ins);
	else if (ins->arg_2[0] == T_LAB)
		lab_writing(info, ins->arg_2, ins);
	else if (ins->arg_2[0])
		ind_writing(info, ins->arg_2);
	if (ins->arg_3[0] == T_REG)
		reg_writing(info, ins->arg_3);
	else if (ins->arg_3[0] == T_DIR)
		dir_writing(info, ins->arg_3, ins);
	else if (ins->arg_3[0] == T_LAB)
		lab_writing(info, ins->arg_3, ins);
	else if (ins->arg_3[0])
		ind_writing(info, ins->arg_3);
}

int			print_instructions(t_info *info)
{
	t_ins	*ins;

	ins = info->ins;
	while (ins->next)
	{
		print_n_bytes(info, ins->op_code, 1);
		if (ins->op_code != 1 && ins->op_code != 9
				&& ins->op_code != 12 && ins->op_code != 15)
			print_argument_type_code(info, ins);
		if (ins->arg_1[0] == T_REG)
			reg_writing(info, ins->arg_1);
		else if (ins->arg_1[0] == T_DIR)
			dir_writing(info, ins->arg_1, ins);
		else if (ins->arg_1[0] == T_LAB)
			lab_writing(info, ins->arg_1, ins);
		else
			ind_writing(info, ins->arg_1);
		print_instructions_bis(info, ins);
		ins = ins->next;
	}
	return (0);
}
