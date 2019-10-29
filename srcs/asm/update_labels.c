/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_labels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:45:57 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/10 14:46:04 by qbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int			assign_pos_to_label_number(int label_number, t_label_list *labels)
{
	t_label_list *tmp;

	tmp = labels;
	while (tmp && tmp->number != label_number)
		tmp = tmp->next;
	if (tmp->pos == -1)
		return (-1);
	return (tmp->pos);
}

static int	update_labels_helper(t_info *info, t_ins *tmp)
{
	if ((tmp->arg_1[0] == T_LAB || tmp->arg_1[0] == T_IND_LAB))
	{
		if ((tmp->arg_1[1] = assign_pos_to_label_number(tmp->arg_1[1], \
			info->labels)) < 0)
			return (-1);
		tmp->arg_1[1] -= tmp->pos;
	}
	if ((tmp->arg_2[0] == T_LAB || tmp->arg_2[0] == T_IND_LAB))
	{
		if ((tmp->arg_2[1] = assign_pos_to_label_number(tmp->arg_2[1], \
			info->labels)) < 0)
			return (-1);
		tmp->arg_2[1] -= tmp->pos;
	}
	if ((tmp->arg_3[0] == T_LAB || tmp->arg_3[0] == T_IND_LAB))
	{
		if ((tmp->arg_3[1] = assign_pos_to_label_number(tmp->arg_3[1], \
			info->labels)) < 0)
			return (-1);
		tmp->arg_3[1] -= tmp->pos;
	}
	return (0);
}

int			update_labels(t_info *info)
{
	t_ins	*tmp;

	tmp = info->ins;
	while (tmp->next)
	{
		if (update_labels_helper(info, tmp))
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
