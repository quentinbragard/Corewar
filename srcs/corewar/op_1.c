/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzimmerm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:09:24 by lzimmerm          #+#    #+#             */
/*   Updated: 2019/09/10 18:10:01 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** Store operation : Write [REG] -> [IND | REG].
*/

void	op_st(t_proc *proc, t_game *game)
{
	short	idx;
	int		i;
	int		reg1;
	int		reg2;

	i = -1;
	if (!coding_byte(game->arena[MODM(proc->pc + 1)], \
		game->op_tab[3].params_type, 0, &proc->jump) \
		&& (reg2 = game->arena[MODM(proc->pc + 2)]) >= 1 && reg2 <= REG_NUMBER)
	{
		if (((game->arena[MODM(proc->pc + 1)] >> 4) & 3) == T_REG \
			&& ((reg1 = game->arena[MODM(proc->pc + 3)]) >= 1 \
			&& reg1 <= REG_NUMBER))
			proc->reg[reg1 - 1] = proc->reg[reg2 - 1];
		else
		{
			idx = MODI(get_short(game->arena, MODM(proc->pc + 3)));
			write_arena(game->arena, MODM(proc->pc + idx), proc->reg[reg2 - 1]);
			while (++i < 4 \
				&& (game->viewer.bold[MODM(proc->pc + idx + i)] = 100))
				game->viewer.color[MODM(proc->pc + idx + i)] = proc->id;
		}
	}
	proc->pc = MODM(proc->pc + proc->jump);
}

/*
** Addition operation : Add [REG] + [REG] -> [REG]
*/

void	op_add(t_proc *proc, t_game *game)
{
	int jump;
	int val;
	int reg;

	if (!coding_byte(game->arena[MODM(proc->pc + 1)], \
		game->op_tab[4].params_type, 0, &jump))
	{
		val = proc->reg[game->arena[MODM(proc->pc + 2)] - 1] \
			+ proc->reg[game->arena[MODM(proc->pc + 3)] - 1];
		reg = game->arena[MODM(proc->pc + 4)] - 1;
		if (reg >= 0 && reg <= REG_NUMBER - 1)
		{
			proc->carry = val ? 0 : 1;
			proc->reg[reg] = val;
		}
	}
	proc->pc = MODM(proc->pc + jump);
}

/*
** Difference operation : Sub [REG] - [REG] -> [REG]
*/

void	op_sub(t_proc *proc, t_game *game)
{
	int jump;
	int val;
	int reg;

	if (!coding_byte(game->arena[MODM(proc->pc + 1)], \
		game->op_tab[5].params_type, 0, &jump))
	{
		val = proc->reg[game->arena[MODM(proc->pc + 2)] - 1] \
			- proc->reg[game->arena[MODM(proc->pc + 3)] - 1];
		reg = game->arena[MODM(proc->pc + 4)] - 1;
		if (reg >= 0 && reg <= REG_NUMBER - 1)
		{
			proc->carry = val ? 0 : 1;
			proc->reg[reg] = val;
		}
	}
	proc->pc = MODM(proc->pc + jump);
}

/*
** Binary and operation : (&) [REG | IND | DIR] & [REG | IND | DIR] -> [REG]
*/

void	op_and(t_proc *proc, t_game *game)
{
	int jump;
	int val1;
	int val2;
	int reg;

	if (!coding_byte(game->arena[MODM(proc->pc + 1)], \
		game->op_tab[6].params_type, 0, &jump) && !(jump = 0))
	{
		proc->jump = 2;
		val1 = get_param(game, proc, \
			((game->arena[MODM(proc->pc + 1)]) >> 6) & 3, 0);
		val2 = get_param(game, proc, \
			((game->arena[MODM(proc->pc + 1)]) >> 4) & 3, 0);
		reg = game->arena[MODM(proc->pc + proc->jump)] - 1;
		if (reg >= 0 && reg <= REG_NUMBER - 1)
		{
			proc->reg[reg] = val1 & val2;
			proc->carry = val1 & val2 ? 0 : 1;
		}
		proc->jump++;
	}
	proc->pc = MODM(proc->pc + jump + proc->jump);
}

/*
** Binary or operation : (|) [REG | IND | DIR] | [REG | IND | DIR] -> [REG]
*/

void	op_or(t_proc *proc, t_game *game)
{
	int jump;
	int val1;
	int val2;
	int reg;

	if (!coding_byte(game->arena[MODM(proc->pc + 1)], \
		game->op_tab[7].params_type, 0, &jump) && !(jump = 0))
	{
		proc->jump = 2;
		val1 = get_param(game, proc, \
			((game->arena[MODM(proc->pc + 1)]) >> 6) & 3, 0);
		val2 = get_param(game, proc, \
			((game->arena[MODM(proc->pc + 1)]) >> 4) & 3, 0);
		reg = game->arena[MODM(proc->pc + proc->jump)] - 1;
		if (reg >= 0 && reg <= REG_NUMBER - 1)
		{
			proc->reg[reg] = val1 | val2;
			proc->carry = val1 | val2 ? 0 : 1;
		}
		proc->jump++;
	}
	proc->pc = MODM(proc->pc + jump + proc->jump);
}
