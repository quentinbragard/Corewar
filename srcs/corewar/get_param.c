/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzimmerm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:44:32 by lzimmerm          #+#    #+#             */
/*   Updated: 2019/09/10 14:45:10 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** Free and remove the proc from the list.
*/

static void	cut_proc(t_proc **prev, t_proc **cur, t_proc *next, t_game *game)
{
	game->player[(*cur)->id - 1].nb_proc -= 1;
	if (!*prev)
	{
		game->proc = next;
		free(*cur);
		*cur = NULL;
	}
	else
	{
		(*prev)->next = next;
		free(*cur);
		*cur = *prev;
	}
}

/*
** Validate the coding byte and set the jump value.
*/

int			coding_byte(unsigned char byte, char par[3], char mod, int *j)
{
	int	count;
	int error;
	int i;

	*j = 2;
	count = 6;
	error = 0;
	i = -1;
	while (++i < 3)
	{
		if (((byte >> count) & 3) == REG_CODE)
			*j += 1;
		else if (((byte >> count) & 3) == IND_CODE)
			*j += 2;
		else if (((byte >> count) & 3) == DIR_CODE)
			*j += mod ? 2 : 4;
		if (!par[i] && (byte >> count) & 3)
			error = 1;
		else if (par[i] && !((par[i] >> (((byte >> count) & 3) - 1)) & 1))
			error = 1;
		count -= 2;
	}
	return (error);
}

/*
** Read one param according to the coding byte and the read size mod.
*/

int			get_param(t_game *game, t_proc *p, char type, char mod)
{
	if (type == REG_CODE && (p->jump += 1))
		return (p->reg[(int)game->arena[MODM(p->pc + p->jump - 1)] - 1]);
	else if (type == IND_CODE && (p->jump += 2))
	{
		if (p->op_code == 13 || p->op_code == 14)
			return ((int)get_int(game->arena, MODM(p->pc \
				+ get_short(game->arena, MODM(p->pc + p->jump - 2)))));
		else
			return ((int)get_int(game->arena, MODM(p->pc \
				+ MODI((short)get_short(game->arena, \
					MODM(p->pc + p->jump - 2))))));
	}
	else if (mod && (p->jump += 2))
		return ((int)MODI(get_short(game->arena, MODM(p->pc + p->jump - 2))));
	else if ((p->jump += 4))
		return ((int)get_int(game->arena, MODM(p->pc + p->jump - 4)));
	return (0);
}

/*
** Refresh the running proc list.
*/

void		kill_proc(t_game *game)
{
	t_proc	*cur;
	t_proc	*next;
	t_proc	*prev;

	prev = NULL;
	cur = game->proc;
	while (cur)
	{
		next = cur->next;
		if (!cur->alive)
			cut_proc(&prev, &cur, next, game);
		else
			cur->alive = 0;
		prev = cur;
		cur = next;
	}
}

/*
** Free all the proc's in the list.
*/

void		free_proc(t_game *game)
{
	t_proc	*to_delete;
	t_proc	*next;

	if ((to_delete = game->proc))
		while (to_delete)
		{
			next = to_delete->next;
			free(to_delete);
			to_delete = next;
		}
	game->proc = NULL;
}
