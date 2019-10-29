/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:39:29 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/10 14:41:11 by qbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int		ft_and(t_info *info, t_ins *ins)
{
	if ((ins->arg_1[0] = possible_args(info, 5, T_REG, T_DIR, T_IND,
					T_LAB, T_IND_LAB)) < 0)
		return (ft_usage(9, info));
	if (((ins->arg_1[1] = get_arg(info, ins->arg_1[0])) < 0)
			&& (ins->arg_1[1] != -1 && info->error == -1))
		return (ft_usage(9, info));
	if (next_arg(info) == -1)
		return (ft_usage(6, info));
	if ((ins->arg_2[0] = possible_args(info, 5, T_REG, T_DIR, T_IND,
					T_LAB, T_IND_LAB)) < 0)
		return (ft_usage(9, info));
	if (((ins->arg_2[1] = get_arg(info, ins->arg_2[0])) < 0)
			&& (ins->arg_2[1] != -1 && info->error == -1))
		return (ft_usage(9, info));
	if (next_arg(info) == -1)
		return (ft_usage(6, info));
	if ((ins->arg_3[0] = possible_args(info, 1, T_REG)) < 0)
		return (ft_usage(9, info));
	if ((ins->arg_3[1] = get_arg(info, ins->arg_3[0])) < 0)
		return (ft_usage(10, info));
	return (0);
}

int		ft_or(t_info *info, t_ins *ins)
{
	if ((ins->arg_1[0] = possible_args(info, 5, T_REG, T_DIR, T_IND,
					T_LAB, T_IND_LAB)) < 0)
		return (ft_usage(9, info));
	if (((ins->arg_1[1] = get_arg(info, ins->arg_1[0])) < 0)
			&& (ins->arg_1[1] != -1 && info->error == -1))
		return (ft_usage(9, info));
	if (next_arg(info) == -1)
		return (ft_usage(6, info));
	if ((ins->arg_2[0] = possible_args(info, 5, T_REG, T_DIR, T_IND,
					T_LAB, T_IND_LAB)) < 0)
		return (ft_usage(9, info));
	if (((ins->arg_2[1] = get_arg(info, ins->arg_2[0])) < 0)
			&& (ins->arg_2[1] != -1 && info->error == -1))
		return (ft_usage(9, info));
	if (next_arg(info) == -1)
		return (ft_usage(6, info));
	if ((ins->arg_3[0] = possible_args(info, 1, T_REG)) < 0)
		return (ft_usage(9, info));
	if ((ins->arg_3[1] = get_arg(info, ins->arg_3[0])) < 0)
		return (ft_usage(10, info));
	return (0);
}

int		ft_xor(t_info *info, t_ins *ins)
{
	if ((ins->arg_1[0] = possible_args(info, 5, T_REG, T_DIR, T_IND,
					T_LAB, T_IND_LAB)) < 0)
		return (ft_usage(9, info));
	if (((ins->arg_1[1] = get_arg(info, ins->arg_1[0])) < 0)
			&& (ins->arg_1[1] != -1 && info->error == -1))
		return (ft_usage(9, info));
	if (next_arg(info) == -1)
		return (ft_usage(6, info));
	if ((ins->arg_2[0] = possible_args(info, 5, T_REG, T_DIR, T_IND,
					T_LAB, T_IND_LAB)) < 0)
		return (ft_usage(9, info));
	if (((ins->arg_2[1] = get_arg(info, ins->arg_2[0])) < 0)
			&& (ins->arg_2[1] != -1 && info->error == -1))
		return (ft_usage(9, info));
	if (next_arg(info) == -1)
		return (ft_usage(6, info));
	if ((ins->arg_3[0] = possible_args(info, 1, T_REG)) < 0)
		return (ft_usage(9, info));
	if ((ins->arg_3[1] = get_arg(info, ins->arg_3[0])) < 0)
		return (ft_usage(10, info));
	return (0);
}

int		ft_zjmp(t_info *info, t_ins *ins)
{
	if ((ins->arg_1[0] = possible_args(info, 2, T_DIR, T_LAB)) < 0)
		return (ft_usage(9, info));
	if (((ins->arg_1[1] = get_arg(info, ins->arg_1[0])) < 0)
			&& (ins->arg_1[1] != -1 && info->error == -1))
		return (ft_usage(9, info));
	return (0);
}

int		ft_ldi(t_info *info, t_ins *ins)
{
	if ((ins->arg_1[0] = possible_args(info, 5, T_REG, T_DIR, T_IND,
					T_LAB, T_IND_LAB)) < 0)
		return (ft_usage(9, info));
	if (((ins->arg_1[1] = get_arg(info, ins->arg_1[0])) < 0)
			&& (ins->arg_1[1] != -1 && info->error == -1))
		return (ft_usage(9, info));
	if (next_arg(info) == -1)
		return (ft_usage(6, info));
	if ((ins->arg_2[0] = possible_args(info, 5, T_IND, T_DIR, T_REG,
					T_IND_LAB, T_LAB)) < 0)
		return (ft_usage(9, info));
	if (((ins->arg_2[1] = get_arg(info, ins->arg_2[0])) < 0)
			&& (ins->arg_2[1] != -1 && info->error == -1))
		return (ft_usage(9, info));
	if (next_arg(info) == -1)
		return (ft_usage(6, info));
	if ((ins->arg_3[0] = possible_args(info, 1, T_REG)) < 0)
		return (ft_usage(9, info));
	if ((ins->arg_3[1] = get_arg(info, ins->arg_3[0])) < 0)
		return (ft_usage(10, info));
	return (0);
}
