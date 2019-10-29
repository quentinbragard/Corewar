/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <bleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 12:25:09 by bleveque          #+#    #+#             */
/*   Updated: 2019/09/10 14:22:04 by qbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int	discover_new_label(t_info *info)
{
	char	*label;
	int		i;
	int		label_number;

	i = 0;
	while (info->file[i] && ft_pos(info->file[i], LABEL_CHARS))
		i++;
	if (info->file[i] != LABEL_CHAR || !i)
		return (ft_usage(6, info));
	if (!(label = ft_strndup(info->file, i)))
		return (ft_usage(-1, info));
	if ((label_number = check_label_exist(info, label)) < 0)
		return (-1);
	if (add_pos_to_label_num(info, label_number) == -1)
		return (-1);
	while (*(info->file) && *(info->file) != LABEL_CHAR)
	{
		info->file++;
		info->column++;
	}
	if (!*(info->file))
		return (ft_usage(6, info));
	info->file++;
	free(label);
	return (0);
}

int	add_label(t_info *info, t_ins *ins)
{
	int i;

	if ((i = discover_new_label(info)) < 0)
		return (-1);
	if ((i = skip_blanks(info)) < 0)
		return (-1);
	i = 0;
	while (is_banned(info->file[i], 5, ' ', '\t', LABEL_CHAR
				, COMMENT_CHAR, ALT_COMMENT_CHAR)
			&& i < ft_pos('\n', info->file))
		i++;
	if (is_authorized(info->file[i], 2, ' ', '\t'))
		return (add_instruction(info, ins));
	if (info->file[i] == LABEL_CHAR)
		return (add_label(info, ins));
	return (add_instruction(info, ins));
}

int	add_label_to_list(t_info *info, char *label_to_create)
{
	t_label_list *tmp;
	t_label_list *new;

	tmp = info->labels;
	while (tmp->next)
		tmp = tmp->next;
	if (!(new = (t_label_list*)malloc(sizeof(t_label_list))))
		return (-1);
	new->name = ft_strdup(label_to_create);
	new->number = tmp->number + 1;
	new->pos = -1;
	new->next = NULL;
	tmp->next = new;
	return (new->number);
}

int	check_label_exist(t_info *info, char *label_to_check)
{
	t_label_list *tmp;

	tmp = info->labels;
	while (tmp)
	{
		if (!ft_strcmp(label_to_check, tmp->name))
		{
			return (tmp->number);
		}
		tmp = tmp->next;
	}
	return (add_label_to_list(info, label_to_check));
}

int	add_pos_to_label_num(t_info *info, int num)
{
	t_label_list	*tmp;

	tmp = info->labels;
	while (tmp)
	{
		if (tmp->number == num)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (-1);
	tmp->pos = info->current_pos;
	return (0);
}
