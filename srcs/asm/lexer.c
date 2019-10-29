/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:17:58 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/10 14:22:50 by qbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int		is_authorized(char to_check, int n, ...)
{
	va_list		ap;
	int			i;
	char		c;

	i = -1;
	if (!to_check)
		return (0);
	va_start(ap, n);
	while (++i < n)
	{
		c = (char)va_arg(ap, int);
		if (to_check == c)
			return (1);
	}
	va_end(ap);
	return (0);
}

int		is_banned(char to_check, int n, ...)
{
	va_list		ap;
	int			i;
	char		c;

	i = -1;
	if (!to_check)
		return (0);
	va_start(ap, n);
	while (++i < n)
	{
		c = (char)va_arg(ap, int);
		if (to_check == c)
			return (0);
	}
	va_end(ap);
	return (1);
}

int		skip_blanks(t_info *info)
{
	while (is_authorized(*(info->file), 5, ' ', '\t', '\n'
				, COMMENT_CHAR, ALT_COMMENT_CHAR))
	{
		if (*(info->file) == '\n')
		{
			info->column = 1;
			info->line++;
		}
		else if (is_authorized(*(info->file), 2
					, COMMENT_CHAR, ALT_COMMENT_CHAR))
		{
			if (ft_pos('\n', info->file))
			{
				info->column = 1;
				info->line++;
				info->file += ft_pos('\n', info->file) - 1;
			}
			else
				return (ft_usage(6, info));
		}
		else
			info->column++;
		info->file++;
	}
	return (0);
}

int		ignore_comments(t_info *info)
{
	if (ft_pos('\n', info->file))
	{
		info->line++;
		info->column = 1;
		info->file += ft_pos('\n', info->file);
	}
	else
		return (ft_usage(6, info));
	return (0);
}
