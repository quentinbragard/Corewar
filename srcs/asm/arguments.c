/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:08:09 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/10 14:09:42 by qbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int		args_to_op_dispatch_bis(t_info *info, t_ins *ins)
{
	if (ins->op_code == 9)
		return (ft_zjmp(info, ins));
	if (ins->op_code == 10)
		return (ft_ldi(info, ins));
	if (ins->op_code == 11)
		return (ft_sti(info, ins));
	if (ins->op_code == 12)
		return (ft_fork(info, ins));
	if (ins->op_code == 13)
		return (ft_lld(info, ins));
	if (ins->op_code == 14)
		return (ft_lldi(info, ins));
	if (ins->op_code == 15)
		return (ft_lfork(info, ins));
	if (ins->op_code == 16)
		return (ft_aff(info, ins));
	return (-1);
}

int		args_to_op_dispatch(t_info *info, t_ins *ins)
{
	if (ins->op_code == 1)
		return (ft_live(info, ins));
	if (ins->op_code == 2)
		return (ft_ld(info, ins));
	if (ins->op_code == 3)
		return (ft_st(info, ins));
	if (ins->op_code == 4)
		return (ft_add(info, ins));
	if (ins->op_code == 5)
		return (ft_sub(info, ins));
	if (ins->op_code == 6)
		return (ft_and(info, ins));
	if (ins->op_code == 7)
		return (ft_or(info, ins));
	if (ins->op_code == 8)
		return (ft_xor(info, ins));
	return (args_to_op_dispatch_bis(info, ins));
}

int		args_counter(t_info *info, t_ins *ins)
{
	int count;
	int i;

	i = -1;
	count = 1;
	while (is_banned(info->file[++i], 3, '\n', COMMENT_CHAR, ALT_COMMENT_CHAR))
		if (info->file[i] == SEPARATOR_CHAR)
			count++;
	return (count == g_op_tab[ins->op_code - 1].nb_params);
}

int		args_recon(t_info *info, t_ins *ins)
{
	int	i;

	i = 0;
	while (is_authorized(*(info->file), 2, ' ', '\t'))
	{
		info->file++;
		info->column++;
	}
	if (is_authorized(*(info->file), 3, '\n', COMMENT_CHAR, ALT_COMMENT_CHAR))
		return (ft_usage(8, info));
	if (args_to_op_dispatch(info, ins) == -1)
		return (-1);
	update_sizes(info, ins);
	return (0);
}
